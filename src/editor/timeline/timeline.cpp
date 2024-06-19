#include "editor/timeline/timeline.h"
#include "editor/timeline/timeline_items.h"

#define OUTER_MARGIN 8

using namespace godot;

void VMTTimeline::_bind_methods() {
}

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

    VBoxContainer *vbox = memnew(VBoxContainer);
    vbox->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
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
    vbox->add_child(scroll);

    Panel *panel = memnew(Panel);
    panel->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    panel->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    scroll->add_child(panel);

    VBoxContainer *rows = memnew(VBoxContainer);
    rows->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    panel->add_child(rows);

    tweens = memnew(VBoxContainer);
    tweens->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    rows->add_child(tweens);

    tweens->add_child(memnew(VMTTween));
    tweens->add_child(memnew(VMTTween));
    tweens->add_child(memnew(VMTTween));

    rows->add_child(memnew(VMTNode));

    sounds = memnew(VBoxContainer);
    sounds->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    rows->add_child(sounds);

    sounds->add_child(memnew(VMTSound));
    sounds->add_child(memnew(VMTSound));
    sounds->add_child(memnew(VMTSound));
    
    
}

VMTTimeline::~VMTTimeline() {
}

void VMTTimeline::add_tween() {
    tweens->add_child(memnew(Button));
}

void VMTTimeline::add_sound() {
}




