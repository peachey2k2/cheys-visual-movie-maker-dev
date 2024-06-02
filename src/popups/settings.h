#pragma once

#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/tab_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/check_box.hpp>
#include <godot_cpp/classes/spin_box.hpp>
#include <godot_cpp/classes/color_picker_button.hpp>
#include <godot_cpp/classes/option_button.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/config_file.hpp>
#include <godot_cpp/classes/file_access.hpp>

#include <map>

#define CATEGORY(m_name)                                                        \
    ScrollContainer *m_name##_scroll = memnew(ScrollContainer);                 \
    m_name##_scroll->set_name(String(#m_name).capitalize());                                         \
    tab_container->add_child(m_name##_scroll);                                  \
    VBoxContainer *m_name##_vbox = memnew(VBoxContainer);                       \
    m_name##_vbox->set_h_size_flags(Control::SIZE_EXPAND_FILL);                 \
    m_name##_vbox->set_v_size_flags(Control::SIZE_EXPAND_FILL);                 \
    m_name##_scroll->add_child(m_name##_vbox);                                  \

namespace godot {
    
class VMTSettingsPopup : public Window {
    GDCLASS(VMTSettingsPopup, Window);

    enum {
        S_BOOLEAN,
        S_INTEGER,
        S_FLOAT,
        S_STRING,
        S_VECTOR2,
        S_COLOR,
        S_ENUM,
    };

    typedef struct {
        int type;
        Variant value;
        Variant def;
        Control *node;
    } Setting;

    typedef struct {
        Variant prev;
        Variant curr;
    } SettingChange;
    
    private:
        TabContainer *tab_container;

        void add_setting(const String p_name, const int p_type, const Variant p_default);
        void define_settings();
        void load_settings();
    
    protected:
        static void _bind_methods();
    
    public:
        VMTSettingsPopup();
        ~VMTSettingsPopup();

        std::map<String, Setting> settings;
        std::map<String, SettingChange> settings_pending = {};
    
        void initialize_settings();
        void setting_edited(const Variant p_value, const String p_name);
        void save_settings();
        void apply_settings();
        void close_popup();
};

class VMTVector2Field : public HBoxContainer {
    GDCLASS(VMTVector2Field, HBoxContainer);

    private:
        Label *label;
        SpinBox *x_field;
        SpinBox *y_field;

    protected:
        static void _bind_methods();

    public:
        VMTVector2Field();
        ~VMTVector2Field();

        void _on_value_changed(const float p_value);

        void set_value(const Vector2 p_value);
        Vector2 get_value();
        void set_min(const Vector2 p_min);
        void set_max(const Vector2 p_max);
        void set_step(const Vector2 p_step);
};

}



