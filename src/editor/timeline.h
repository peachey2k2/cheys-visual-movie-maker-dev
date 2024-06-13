#pragma once

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

namespace godot {

class VMTTimeline : public Panel {
    GDCLASS(VMTTimeline, Panel);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTTimeline();
        ~VMTTimeline();

};

}