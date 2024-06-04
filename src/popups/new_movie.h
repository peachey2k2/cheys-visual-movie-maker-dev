#pragma once

#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/style_box.hpp>
#include <godot_cpp/classes/style_box_flat.hpp>

namespace godot {

class VMTNewMoviePopup : public Window {
    GDCLASS(VMTNewMoviePopup, Window);

    private:
        LineEdit *name_input;

        void _on_create_pressed();
        void _on_cancel_pressed();
    
    protected:
        static void _bind_methods();

    public:
        VMTNewMoviePopup();
        ~VMTNewMoviePopup();

        void _popup();
        void close_popup();
};

}