#include "popups/settings.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include "editor/tab.h"

#define OUTER_MARGIN 3
#define SETTINGS_FILE VisualMovieTab::get_singleton()->get_movie()->path + "settings.cfg"

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
    add_setting("test_boolean", S_BOOLEAN, false);
    add_setting("test_bool_2", S_BOOLEAN, false);
    add_setting("test_bool_3", S_BOOLEAN, false);
    add_setting("test_bool_4", S_BOOLEAN, false);
    add_setting("test_integer", S_INTEGER, 0);
    add_setting("test_float", S_FLOAT, 0.0);
    add_setting("test_string", S_STRING, "test");
    add_setting("test_vector2", S_VECTOR2, Vector2(0, 0));
    add_setting("test_color", S_COLOR, Color(0, 0, 0, 1));
    add_setting("test_enum", S_ENUM, Array::make("Option 1", "Option 2", "Option 3"));
    CATEGORY(advanced);
    add_setting("test_boolean", S_BOOLEAN, false);
    add_setting("test_integer", S_INTEGER, 0);
}

VMTSettingsPopup::~VMTSettingsPopup() {
}

void VMTSettingsPopup::setting_edited(const Variant p_value, const String p_name) {
    UtilityFunctions::print(p_name, ": ", settings[p_name].value, "->", p_value);
    settings_pending[p_name] = {settings[p_name].value, p_value};
}

void VMTSettingsPopup::add_setting(const String p_name, const int p_type, const Variant p_default) {
    ScrollContainer *tab = static_cast<ScrollContainer*>(tab_container->get_child(-1)->get_child(0));
    HBoxContainer *setting = memnew(HBoxContainer);
    tab->add_child(setting);
    String full_name = tab_container->get_child(-1)->get_name().to_snake_case() + String("/") + p_name;

    Label *label = memnew(Label);
    label->set_text(p_name.capitalize());
    setting->add_child(label);
    label->set_h_size_flags(Control::SIZE_EXPAND_FILL);

    if (p_type != S_VECTOR2) {
        settings[full_name] = {p_type, p_default, p_default};
    }

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
            spinbox->set_min(0);
            spinbox->set_max(100);
            spinbox->set_value(p_default);
            setting->add_child(spinbox);
            spinbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);
            spinbox->connect("value_changed", Callable(this, "setting_edited").bind(full_name));
            settings[full_name].node = spinbox;
            break;
        }
        case S_FLOAT: {
            SpinBox *spinbox = memnew(SpinBox);
            spinbox->set_min(0);
            spinbox->set_max(1);
            spinbox->set_step(0.01);
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
            HBoxContainer *hbox = memnew(HBoxContainer);
            setting->add_child(hbox);
            hbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);

            SpinBox *spinbox_x = memnew(SpinBox);
            spinbox_x->set_min(0);
            spinbox_x->set_max(100);
            spinbox_x->set_value(p_default);
            hbox->add_child(spinbox_x);
            spinbox_x->set_h_size_flags(Control::SIZE_EXPAND_FILL);

            SpinBox *spinbox_y = memnew(SpinBox);
            spinbox_y->set_min(0);
            spinbox_y->set_max(100);
            spinbox_y->set_value(p_default);
            hbox->add_child(spinbox_y);
            spinbox_y->set_h_size_flags(Control::SIZE_EXPAND_FILL);

            spinbox_x->connect("value_changed", Callable(this, "setting_edited").bind(String(full_name) + "_x"));
            spinbox_y->connect("value_changed", Callable(this, "setting_edited").bind(String(full_name) + "_y"));

            Vector2 vec = p_default;
            settings[full_name + "_x"] = {S_VECTOR2, vec.x, vec.x, spinbox_x};   
            settings[full_name + "_y"] = {S_VECTOR2, vec.y, vec.y, spinbox_y};
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
            Array options = p_default;
            for (int i = 0; i < options.size(); i++) {
                optionbutton->add_item(options[i]);
            }
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
                if (setting.ends_with("_x")) {
                    static_cast<SpinBox*>(settings[setting].node)->set_value(value);
                } else {
                    static_cast<SpinBox*>(settings[setting].node)->set_value(value);
                }
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




