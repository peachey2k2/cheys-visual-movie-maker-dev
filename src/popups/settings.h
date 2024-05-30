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


#define CATEGORY(m_name)                                                        \
    ScrollContainer *m_name##_scroll = memnew(ScrollContainer);                 \
    m_name##_scroll->set_name(#m_name);                                         \
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
    
    private:
        void add_setting(const String p_name, const int p_type, const Variant p_default);

        TabContainer *tab_container;
    
    protected:
        static void _bind_methods();
    
    public:
        VMTSettingsPopup();
        ~VMTSettingsPopup();
    
        void define_settings();
        void setting_changed(const Variant p_value, const String p_name);
};

}
