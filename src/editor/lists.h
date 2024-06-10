#pragma once

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/tree.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/style_box.hpp>
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/editor_settings.hpp>

#define ADD_BUTTON(m_parent, m_name, m_tooltip, m_icon)                                                            \
    Button *m_name = memnew(Button);                                                                    \
    m_name->add_theme_icon_override(                                                                    \
        "icon",                                                                                         \
        EditorInterface::get_singleton()->get_base_control()->get_theme_icon(m_icon, "EditorIcons")     \
    );                                                                                                  \
    m_name->set_tooltip_text(m_tooltip);                                                                \
    m_parent->add_child(m_name);                                                                        \

namespace godot {

class VMTList : public Panel {
    GDCLASS(VMTList, Panel);

    private:
        Tree *list;
        Label *title;

        // Ref<DirAccess> dir;
        String dir = "";

    protected:
        static void _bind_methods();

        void set_title(const String &p_title) { title->set_text(p_title); }
        void set_directory(const String &p_directory);

    public:
        VMTList();
        ~VMTList();

        void _ready() override;
        virtual void _on_movie_opened(const String &name) { return; };
        void update_files();

};

class VMTScriptList : public VMTList {
    GDCLASS(VMTScriptList, VMTList);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTScriptList();
        ~VMTScriptList();

        void _on_movie_opened(const String &name) override;

};

class VMTFilterList : public VMTList {
    GDCLASS(VMTFilterList, VMTList);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTFilterList();
        ~VMTFilterList();

        void _on_movie_opened(const String &name) override;


};

}