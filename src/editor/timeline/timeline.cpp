#include "editor/timeline/timeline.h"
#include "editor/timeline/timeline_items.h"

#define OUTER_MARGIN 8

using namespace godot;

void VMTTimeline::_bind_methods() {
}

void VMTTimeline::_ready() {
    MarginContainer *margin = memnew(MarginContainer);
    margin->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->begin_bulk_theme_override();
    margin->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin->end_bulk_theme_override();
    add_child(margin);

    VBoxContainer *vbox = memnew(VBoxContainer);
    // vbox->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->add_child(vbox);

    HFlowContainer *hotbar = memnew(HFlowContainer);
    // TODO: placeholder buttons, change later
    ADD_BUTTON(hotbar, new_script, "New Script", "ScriptCreate");
    ADD_BUTTON(hotbar, remove_script, "Remove Script", "ScriptRemove");
    ADD_BUTTON(hotbar, new_folder, "New Folder", "FolderCreate");
    ADD_BUTTON(hotbar, remove_folder, "Remove Folder", "Folder");
    ADD_BUTTON(hotbar, rename, "Rename", "Rename");
    vbox->add_child(hotbar);

    ScrollContainer *scroll = memnew(ScrollContainer);
    scroll->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    scroll->set_horizontal_scroll_mode(ScrollContainer::SCROLL_MODE_SHOW_ALWAYS);
    scroll->set_vertical_scroll_mode(ScrollContainer::SCROLL_MODE_SHOW_ALWAYS);
    vbox->add_child(scroll);

    Panel *panel = memnew(Panel);
    panel->set_custom_minimum_size(Size2(10000, VMTTimelineItem::TOTAL_HEIGHT));
    panel->add_theme_stylebox_override("panel", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("panel", "Tree"));
    scroll->add_child(panel);

    panel->add_child(VMTTween::create(0, 200, 0));
    panel->add_child(VMTTween::create(100, 300, 1));
    panel->add_child(VMTTween::create(200, 400, 2));
    panel->add_child(VMTNode::create(memnew(Node)));
    panel->add_child(VMTSound::create(0, 200, 0));
    panel->add_child(VMTSound::create(100, 300, 1));
    panel->add_child(VMTSound::create(200, 400, 2));
    
}

VMTTimeline::VMTTimeline() {
}

VMTTimeline::~VMTTimeline() {
}

void VMTTimeline::add_tween() {
}

void VMTTimeline::add_sound() {
}




