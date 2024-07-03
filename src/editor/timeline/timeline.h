#pragma once

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/h_scroll_bar.hpp>
#include <godot_cpp/classes/input.hpp>

#include "defines.h"
#include "editor/timeline/ruler.h"

namespace godot {

class VMTTimeline : public Panel {
    GDCLASS(VMTTimeline, Panel);

    private:
        Panel *panel;
        VMTTimelineRuler *ruler;
        ScrollContainer *scroll;

        float zoom_factor = 1.0;

        void add_tween();
        void add_sound();

    protected:
        static void _bind_methods();

    public:
        VMTTimeline();
        ~VMTTimeline();

        void _process(float p_delta);
        void _ready() override;

        float get_zoom_factor() const { return zoom_factor; }

        Rect2 get_timeline_visible_rect() const;
        void _on_gui_input(const InputEvent *p_event);

};

}