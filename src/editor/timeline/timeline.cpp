#include "editor/timeline/timeline.h"
#include "editor/timeline/timeline_items.h"

#include <godot_cpp/variant/utility_functions.hpp>

#define OUTER_MARGIN 8

using namespace godot;

void VMTTimeline::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_gui_input"), &VMTTimeline::_on_gui_input);
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
    margin->add_child(vbox);

    HFlowContainer *hotbar = memnew(HFlowContainer);
    // TODO: placeholder buttons, change later
    ADD_BUTTON(hotbar, new_script, "New Script", "ScriptCreate");
    ADD_BUTTON(hotbar, remove_script, "Remove Script", "ScriptRemove");
    ADD_BUTTON(hotbar, new_folder, "New Folder", "FolderCreate");
    ADD_BUTTON(hotbar, remove_folder, "Remove Folder", "Folder");
    ADD_BUTTON(hotbar, rename, "Rename", "Rename");
    vbox->add_child(hotbar);

    ruler = memnew(VMTTimelineRuler);
    vbox->add_child(ruler);

    scroll = memnew(ScrollContainer);
    scroll->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    scroll->set_horizontal_scroll_mode(ScrollContainer::SCROLL_MODE_SHOW_ALWAYS);
    scroll->set_vertical_scroll_mode(ScrollContainer::SCROLL_MODE_SHOW_ALWAYS);
    scroll->get_h_scroll_bar()->connect("scrolling", Callable(ruler, "queue_redraw"));
    scroll->connect("gui_input", Callable(this, "_on_gui_input"));
    vbox->add_child(scroll);

    panel = memnew(Panel);
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

void VMTTimeline::_process(float p_delta) {
    auto [item, dir, offset] = VMTTimelineItem::cur_draggable;
    if (item != nullptr) {
        Vector2 mouse_pos = panel->get_local_mouse_position();
        switch (dir) {
            case VMTTimelineItem::LEFT:
                item->resize(mouse_pos.x / zoom_factor, item->get_end_frame());
                break;
            case VMTTimelineItem::RIGHT:
                item->resize(item->get_start_frame(), mouse_pos.x / zoom_factor);
                break;
            case VMTTimelineItem::MIDDLE:
                item->move((mouse_pos.x - offset) / zoom_factor, item->to_row(mouse_pos.y));
                break;
        }
    }
}

VMTTimeline::VMTTimeline() {
    // VMTTimelineItem::cur_draggable.first = nullptr;
}

VMTTimeline::~VMTTimeline() {
}

void VMTTimeline::add_tween() {
}

void VMTTimeline::add_sound() {
}

Rect2 VMTTimeline::get_timeline_visible_rect() const {
    return Rect2(scroll->get_h_scroll(), scroll->get_v_scroll(), scroll->get_size().x, scroll->get_size().y);
}

void VMTTimeline::_on_gui_input(const InputEvent *p_event) {
    if (Input::get_singleton()->is_key_pressed(KEY_CTRL)) {
        auto e = dynamic_cast<const InputEventMouseButton*>(p_event);
        if (e == nullptr) return;
        if (!e->is_pressed()) return;
        if (e->get_button_index() == MouseButton::MOUSE_BUTTON_WHEEL_UP) {
            if (zoom_factor > 50) return;
            zoom_factor *= 1 + e->get_factor();
            queue_redraw();
            ruler->queue_redraw();
        } else if (e->get_button_index() == MouseButton::MOUSE_BUTTON_WHEEL_DOWN) {
            if (zoom_factor < 1/50) return;
            zoom_factor /= 1 + e->get_factor();
            queue_redraw();
            ruler->queue_redraw();
        }
        for (int i = 0; i < panel->get_child_count(); i++) {
            Object::cast_to<VMTTimelineItem>(panel->get_child(i))->refresh_position();
        }
        // hack to overwrite godot's scroll behavior
        get_tree()->connect(
            "process_frame",
            Callable(scroll->get_v_scroll_bar(), "set_value").bind(scroll->get_v_scroll_bar()->get_value()),
            CONNECT_DEFERRED + CONNECT_ONE_SHOT + CONNECT_REFERENCE_COUNTED
        );
    }
    UtilityFunctions::print("Zoom factor: " + String::num(zoom_factor));
}



