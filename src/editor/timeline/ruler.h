#pragma once

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/font.hpp>
#include <godot_cpp/classes/theme_db.hpp>

#include "editor/timeline/timeline.h"

namespace godot {

class VMTTimelineRuler : public Panel {
    GDCLASS(VMTTimelineRuler, Panel);

    private:
        VMTTimeline *timeline;
        Ref<Font> def_font;

    protected:
        static void _bind_methods();

    public:
        VMTTimelineRuler();
        ~VMTTimelineRuler();

        void _draw() override;


};

}