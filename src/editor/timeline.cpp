#include "editor/timeline.h"

#define OUTER_MARGIN 8

using namespace godot;

VMTTimeline::VMTTimeline() {
    MarginContainer *margin = memnew(MarginContainer);
    margin->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->begin_bulk_theme_override();
    margin->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin->end_bulk_theme_override();
    add_child(margin);

    ScrollContainer *scroll = memnew(ScrollContainer);
    scroll->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->add_child(scroll);

    
}

VMTTimeline::~VMTTimeline() {
}

void VMTTimeline::_bind_methods() {
}




