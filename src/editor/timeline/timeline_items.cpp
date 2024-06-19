#include "editor/timeline/timeline_items.h"

using namespace godot;

/******* VMTTimeline methods *******/

void VMTTimelineItem::_bind_methods() {
}

VMTTimelineItem::VMTTimelineItem() {
}

VMTTimelineItem::~VMTTimelineItem() {
}

/******* VMTTween methods *******/

void VMTTween::_bind_methods() {
}

VMTTween::VMTTween() {
    set_custom_minimum_size(Size2(0, 32));
    add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg3", "EditorStyles"));
}

VMTTween::~VMTTween() {
}

/******* VMTNode methods *******/

void VMTNode::_bind_methods() {
}

VMTNode::VMTNode() {
    set_custom_minimum_size(Size2(0, 48));
    add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg16", "EditorStyles"));
}

VMTNode::~VMTNode() {
}

/******* VMTSound methods *******/

void VMTSound::_bind_methods() {
}

VMTSound::VMTSound() {
    set_custom_minimum_size(Size2(0, 32));
    add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg14", "EditorStyles"));
}

VMTSound::~VMTSound() {
}


