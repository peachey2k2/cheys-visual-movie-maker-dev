#pragma once

#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/button.hpp>

#include "editor/timeline/timeline_items.h"

namespace godot {

class VMTEditTweenPopup : public Window {
    GDCLASS(VMTEditTweenPopup, Window);

    private:
        void _on_save_pressed();
        void _on_cancel_pressed();
    
    protected:
        static void _bind_methods();

    public:
        VMTEditTweenPopup();
        ~VMTEditTweenPopup();

        void _popup(VMTTimelineItem *p_item);
        void close_popup();
};

}