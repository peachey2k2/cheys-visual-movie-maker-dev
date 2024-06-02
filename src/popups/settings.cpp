#include "popups/settings.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include "editor/tab.h"

#define OUTER_MARGIN 3
#define SETTINGS_FILE VisualMovieTab::get_singleton()->get_movie()->path + "project.cvmm"

using namespace godot;

void VMTSettingsPopup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize_settings"), &VMTSettingsPopup::initialize_settings);
    ClassDB::bind_method(D_METHOD("setting_edited", "p_value", "p_name"), &VMTSettingsPopup::setting_edited);
    ClassDB::bind_method(D_METHOD("save_settings"), &VMTSettingsPopup::save_settings);
    ClassDB::bind_method(D_METHOD("apply_settings"), &VMTSettingsPopup::apply_settings);
    ClassDB::bind_method(D_METHOD("close_popup"), &VMTSettingsPopup::close_popup);
}

VMTSettingsPopup::VMTSettingsPopup() {
    connect("close_requested", Callable(this, "close_popup"));
    hide();

    set_size(Size2(400, 300));
    set_title("Settings");
    set_flag(Window::FLAG_RESIZE_DISABLED, true);
    set_flag(Window::FLAG_ALWAYS_ON_TOP, false);

    Panel *panel = memnew(Panel);
    panel->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    add_child(panel);

    MarginContainer *margin_container = memnew(MarginContainer);
    margin_container->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin_container->begin_bulk_theme_override();
    margin_container->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin_container->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin_container->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin_container->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin_container->end_bulk_theme_override();
    add_child(margin_container);

    VBoxContainer *vbox = memnew(VBoxContainer);
    vbox->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin_container->add_child(vbox);

    tab_container = memnew(TabContainer);
    tab_container->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    tab_container->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    vbox->add_child(tab_container);

    HBoxContainer *buttons = memnew(HBoxContainer);
    buttons->set_alignment(BoxContainer::ALIGNMENT_CENTER);
    vbox->add_child(buttons);

    Button *apply = memnew(Button);
    apply->set_text("Apply");
    buttons->add_child(apply);
    apply->connect("pressed", Callable(this, "apply_settings"));

    Button *save = memnew(Button);
    save->set_text("Save");
    buttons->add_child(save);
    save->connect("pressed", Callable(this, "save_settings"));
    
    Button *cancel = memnew(Button);
    cancel->set_text("Cancel");
    buttons->add_child(cancel);
    cancel->connect("pressed", Callable(this, "close_popup"));

    // pro tip: if something doesn't work, just add a delay
    connect("ready", Callable(this, "initialize_settings"), CONNECT_ONE_SHOT + CONNECT_DEFERRED);
}

void VMTSettingsPopup::define_settings() {
    CATEGORY(general);
    add_setting("project_name", S_STRING, "New Project");
    add_setting("viewport_dimensions", S_VECTOR2, Vector2(1280, 720), Array::make(Vector2(1, 1), Vector2(4096, 4096), Vector2(1, 1)));
    add_setting("background_color", S_COLOR, Color(0.5, 0.5, 0.5, 1));
}

VMTSettingsPopup::~VMTSettingsPopup() {
}

void VMTSettingsPopup::setting_edited(const Variant p_value, const String p_name) {
    UtilityFunctions::print(p_name, ": ", settings[p_name].value, "->", p_value);
    settings_pending[p_name] = {settings[p_name].value, p_value};
}

void VMTSettingsPopup::add_setting(const String p_name, const int p_type, const Variant p_default, const Array p_extra) {
    ScrollContainer *tab = static_cast<ScrollContainer*>(tab_container->get_child(-1)->get_child(0));
    HBoxContainer *setting = memnew(HBoxContainer);
    tab->add_child(setting);
    String full_name = tab_container->get_child(-1)->get_name().to_snake_case() + String("/") + p_name;

    Label *label = memnew(Label);
    label->set_text(p_name.capitalize());
    setting->add_child(label);
    label->set_h_size_flags(Control::SIZE_EXPAND_FILL);

    settings[full_name] = {p_type, p_default, p_default};

    switch (p_type) {
        case S_BOOLEAN: {
            CheckBox *checkbox = memnew(CheckBox);
            checkbox->set_pressed(p_default);
            setting->add_child(checkbox);
            checkbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            checkbox->connect("toggled", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = checkbox;
            break;
        }
        case S_INTEGER: {
            SpinBox *spinbox = memnew(SpinBox);
            spinbox->set_min(p_extra[0]);
            spinbox->set_max(p_extra[1]);
            spinbox->set_step(1);
            spinbox->set_value(p_default);
            setting->add_child(spinbox);
            spinbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            spinbox->connect("value_changed", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = spinbox;
            break;
        }
        case S_FLOAT: {
            SpinBox *spinbox = memnew(SpinBox);
            spinbox->set_min(p_extra[0]);
            spinbox->set_max(p_extra[1]);
            spinbox->set_step(p_extra[2]);
            spinbox->set_value(p_default);
            setting->add_child(spinbox);
            spinbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            spinbox->connect("value_changed", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = spinbox;
            break;
        }
        case S_STRING: {
            LineEdit *lineedit = memnew(LineEdit);
            lineedit->set_text(p_default);
            setting->add_child(lineedit);
            lineedit->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            lineedit->connect("text_changed", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = lineedit;
            break;
        }
        case S_VECTOR2: {
            VMTVector2Field *field = memnew(VMTVector2Field);
            field->set_min(Vector2(p_extra[0]));
            field->set_max(Vector2(p_extra[1]));
            field->set_step(Vector2(p_extra[2]));
            field->set_value(p_default);
            setting->add_child(field);
            field->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            Error err = field->connect("value_changed", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = field;
            break;
        }
        case S_COLOR: {
            ColorPickerButton *colorpicker = memnew(ColorPickerButton);
            colorpicker->set_pick_color(p_default);
            setting->add_child(colorpicker);
            colorpicker->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            colorpicker->connect("color_changed", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = colorpicker;
            break;
        }
        case S_ENUM: {
            OptionButton *optionbutton = memnew(OptionButton);
            for (int i = 0; i < p_extra.size(); i++) {
                optionbutton->add_item(p_extra[i]);
            }
            optionbutton->select(p_default);
            setting->add_child(optionbutton);
            optionbutton->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            optionbutton->connect("item_selected", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = optionbutton;
            break;
        }
    }
}

void VMTSettingsPopup::initialize_settings() {
    define_settings();
    load_settings();
    settings_pending = {};
}

void VMTSettingsPopup::load_settings() {
    ConfigFile *config = memnew(ConfigFile);
    Error err = config->load(SETTINGS_FILE);
    if (err != OK) {
        UtilityFunctions::printerr("Failed to load settings file: ", SETTINGS_FILE);
        return;
    }
    for (auto [setting, data] : settings) {
        Variant value = config->get_value(setting.get_slice("/", 0), setting.get_slice("/", 1), data.def);
        settings[setting].value = value;
        UtilityFunctions::print("Setting loaded: ", setting, " = ", value);
        switch (settings[setting].type) {
            case S_BOOLEAN: {
                static_cast<CheckBox*>(settings[setting].node)->set_pressed(value);
                break;
            }
            case S_INTEGER: {
                static_cast<SpinBox*>(settings[setting].node)->set_value(value);
                break;
            }
            case S_FLOAT: {
                static_cast<SpinBox*>(settings[setting].node)->set_value(value);
                break;
            }
            case S_STRING: {
                static_cast<LineEdit*>(settings[setting].node)->set_text(value);
                break;
            }
            case S_VECTOR2: {
                static_cast<VMTVector2Field*>(settings[setting].node)->set_value(value);
                break;
            }
            case S_COLOR: {
                static_cast<ColorPickerButton*>(settings[setting].node)->set_pick_color(value);
                break;
            }
            case S_ENUM: {
                static_cast<OptionButton*>(settings[setting].node)->select(value);
                break;
            }
        
        }
    }
}

void VMTSettingsPopup::save_settings() {
    apply_settings();
    close_popup();
}

void VMTSettingsPopup::apply_settings() {
    ConfigFile *config = memnew(ConfigFile);
    Error err = config->load(SETTINGS_FILE);
    if (err != OK) {
        UtilityFunctions::printerr("Failed to load settings file: ", SETTINGS_FILE);
        Ref<FileAccess> file = FileAccess::open(SETTINGS_FILE, FileAccess::WRITE);
        err = file->get_open_error();
        if (err != OK) {
            UtilityFunctions::printerr("Failed to create settings file: ", SETTINGS_FILE);
        }
        return;
    }
    for (auto [setting, change] : settings_pending) {
        if (settings[setting].value == change.curr) {
            continue;
        }
        if (change.curr == settings[setting].def) {
            config->set_value(setting.get_slice("/", 0), setting.get_slice("/", 1), nullptr);
        }
        settings[setting].value = change.curr;
        config->set_value(setting.get_slice("/", 0), setting.get_slice("/", 1), change.curr);
        UtilityFunctions::print("Setting saved: ", setting, " = ", change.curr);
        
    }
    config->save(SETTINGS_FILE);
    settings_pending = {};
}

void VMTSettingsPopup::close_popup() {
    load_settings();
    hide();
}

void VMTVector2Field::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_value_changed", "p_value"), &VMTVector2Field::_on_value_changed);
    ADD_SIGNAL(MethodInfo("value_changed", PropertyInfo(Variant::VECTOR2, "value")));
}

void VMTVector2Field::_on_value_changed(const float p_value) {
    emit_signal("value_changed", get_value());
    UtilityFunctions::print("VMTVector2Field value changed: ", get_value());
}

VMTVector2Field::VMTVector2Field() {
    x_field = memnew(SpinBox);
    x_field->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    add_child(x_field);
    x_field->connect("value_changed", Callable(this, "_on_value_changed"), CONNECT_DEFERRED);

    y_field = memnew(SpinBox);
    y_field->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    add_child(y_field);
    y_field->connect("value_changed", Callable(this, "_on_value_changed"), CONNECT_DEFERRED);
}

VMTVector2Field::~VMTVector2Field() {
}

void VMTVector2Field::set_value(const Vector2 p_value) {
    x_field->set_value(p_value.x);
    y_field->set_value(p_value.y);
}

Vector2 VMTVector2Field::get_value() {
    return Vector2(x_field->get_value(), y_field->get_value());
}

void VMTVector2Field::set_min(const Vector2 p_min) {
    x_field->set_min(p_min.x);
    y_field->set_min(p_min.y);
}

void VMTVector2Field::set_max(const Vector2 p_max) {
    x_field->set_max(p_max.x);
    y_field->set_max(p_max.y);
}

void VMTVector2Field::set_step(const Vector2 p_step) {
    x_field->set_step(p_step.x);
    y_field->set_step(p_step.y);
}


