#pragma once

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/editor_interface.hpp>

#include "defines.h"

namespace godot {

class VMTTimeline : public Panel {
    GDCLASS(VMTTimeline, Panel);

    private:
        VBoxContainer *tweens;
        VBoxContainer *sounds;

        void add_tween();
        void add_sound();

    protected:
        static void _bind_methods();

    public:
        VMTTimeline();
        ~VMTTimeline();

};

}