#include "editor/timeline/timeline_items.h"

#include "editor/tab.h"

using namespace godot;

/******* Statics *******/

VMTTimelineItem::DragData VMTTimelineItem::cur_draggable = DragData{nullptr, LEFT, 0.0};

/******* VMTTimelineItem methods *******/

void VMTTimelineItem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_pressed"), &VMTTimelineItem::_on_pressed);
    ClassDB::bind_method(D_METHOD("_on_gui_input_left"), &VMTTimelineItem::_on_gui_input_left);
    ClassDB::bind_method(D_METHOD("_on_gui_input_right"), &VMTTimelineItem::_on_gui_input_right);
    ClassDB::bind_method(D_METHOD("_on_gui_input_middle"), &VMTTimelineItem::_on_gui_input_middle);
}

VMTTimelineItem::VMTTimelineItem() {
    l_handle = memnew(Control);
    l_handle->set_custom_minimum_size(Size2(4, 0));
    // l_handle->set_h_size_flags(Control::SIZE_SHRINK_BEGIN);
    // l_handle->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    l_handle->set_anchors_and_offsets_preset(Control::PRESET_LEFT_WIDE);
    l_handle->set_default_cursor_shape(Control::CURSOR_HSIZE);
    l_handle->connect("gui_input", Callable(this, "_on_gui_input_left"));
    add_child(l_handle);

    r_handle = memnew(Control);
    r_handle->set_custom_minimum_size(Size2(4, 0));
    // r_handle->set_h_size_flags(Control::SIZE_SHRINK_END);
    // r_handle->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    r_handle->set_anchors_and_offsets_preset(Control::PRESET_RIGHT_WIDE);
    r_handle->set_default_cursor_shape(Control::CURSOR_HSIZE);
    r_handle->connect("gui_input", Callable(this, "_on_gui_input_right"));
    add_child(r_handle);

    connect("pressed", Callable(this, "_on_pressed"));
    connect("gui_input", Callable(this, "_on_gui_input_middle"));
    set_clip_text(true);
}

void VMTTimelineItem::_ready() {
    refresh_position();
}

VMTTimelineItem::~VMTTimelineItem() {
}

void VMTTimelineItem::_on_pressed() {
    // UtilityFunctions::print(l_handle->get_position(), " ", r_handle->get_position());
}

void VMTTimelineItem::_on_gui_input_left(const InputEvent *p_event) {
    auto e = dynamic_cast<const InputEventMouseButton*>(p_event);
    if (e == nullptr) return;
    if (e->get_button_index() != MouseButton::MOUSE_BUTTON_LEFT) return;
    if (e->is_pressed()) {
        cur_draggable = DragData{this, LEFT, (float)get_local_mouse_position().x};
    } else {
        cur_draggable.item = nullptr;
    }
}

void VMTTimelineItem::_on_gui_input_right(const InputEvent *p_event) {
    auto e = dynamic_cast<const InputEventMouseButton*>(p_event);
    if (e == nullptr) return;
    if (e->get_button_index() != MouseButton::MOUSE_BUTTON_LEFT) return;
    if (e->is_pressed()) {
        cur_draggable = DragData{this, RIGHT, (float)get_local_mouse_position().x};
    } else {
        cur_draggable.item = nullptr;
    }
}

void VMTTimelineItem:: _on_gui_input_middle(const InputEvent *p_event) {
    auto e = dynamic_cast<const InputEventMouseButton*>(p_event);
    if (e == nullptr) return;
    if (e->get_button_index() != MouseButton::MOUSE_BUTTON_LEFT) return;
    if (e->is_double_click()) {
        VisualMovieTab::get_singleton()->get_edit_tween_popup()->_popup(this);
    } else {
        if (e->is_pressed()) {
            cur_draggable = DragData{this, MIDDLE, (float)get_local_mouse_position().x};
        } else {
            cur_draggable.item = nullptr;
        }
    }
}

void VMTTimelineItem::set_start_frame(int p_start) {
    start_frame = p_start;
    refresh_position();
}

void VMTTimelineItem::set_end_frame(int p_end) {
    end_frame = p_end;
    refresh_position();
}

void VMTTimelineItem::set_row(int p_row) {
    row = p_row;
    refresh_position();
}

void VMTTimelineItem::resize(int p_start, int p_end) {
    if (end_frame < start_frame) return;
    if (start_frame < 0) start_frame = 0;
    set_start_frame(p_start);
    set_end_frame(p_end);
}

void VMTTimelineItem::move(int p_dest_frame, int p_dest_row) {
    if (p_dest_row < 0) p_dest_row = 0;
    if (p_dest_frame < 0) p_dest_frame = 0;
    end_frame = p_dest_frame + get_length();
    start_frame = p_dest_frame;
    row = p_dest_row;
    refresh_position();
}

/******* VMTTween methods *******/

void VMTTween::_bind_methods() {
}

VMTTween::VMTTween() {
    set_custom_minimum_size(Size2(0, TWEEN_HEIGHT));
    add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg3", "EditorStyles"));
    add_theme_stylebox_override("hover", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg3", "EditorStyles"));
    set_text("example tween");
}

VMTTween::~VMTTween() {
}

VMTTween *VMTTween::create(int p_start, int p_end, int p_row) {
    VMTTween *tween = memnew(VMTTween);
    tween->start_frame = p_start;
    tween->end_frame = p_end;
    tween->row = p_row;
    tween->refresh_position();
    return tween;
}

void VMTTween::refresh_position() {
    float zoom_factor = VisualMovieTab::get_singleton()->get_timeline()->get_zoom_factor();
    set_position(Vector2(start_frame * zoom_factor, NODE_POS - ((row+1) * TWEEN_HEIGHT)));
    set_size(Vector2(get_length() * zoom_factor, TWEEN_HEIGHT));
}

int VMTTween::to_row(float p_height) const {
    return (NODE_POS - p_height) / TWEEN_HEIGHT;
}

/******* VMTNode methods *******/

void VMTNode::_bind_methods() {
}

VMTNode::VMTNode() {
    set_custom_minimum_size(Size2(0, NODE_HEIGHT));
    add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg16", "EditorStyles"));
    add_theme_stylebox_override("hover", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg16", "EditorStyles"));
    set_text("example node");
    resize(0, 500);
}

VMTNode::~VMTNode() {
}

VMTNode *VMTNode::create(Node *p_root) {
    VMTNode *node = memnew(VMTNode);
    node->refresh_position();
    return node;
}

void VMTNode::refresh_position() {
    float zoom_factor = VisualMovieTab::get_singleton()->get_timeline()->get_zoom_factor();
    set_position(Vector2(start_frame * zoom_factor, NODE_POS));
    set_size(Vector2(get_length() * zoom_factor, NODE_HEIGHT));
}

int VMTNode::to_row(float p_height) const {
    return 0;
}

/******* VMTSound methods *******/

void VMTSound::_bind_methods() {
}

VMTSound::VMTSound() {
    set_custom_minimum_size(Size2(0, SOUND_HEIGHT));
    add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg14", "EditorStyles"));
    add_theme_stylebox_override("hover", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("sub_inspector_bg14", "EditorStyles"));
    set_text("example sound");
}

VMTSound::~VMTSound() {
}

VMTSound *VMTSound::create(int p_start, int p_end, int p_row) {
    VMTSound *sound = memnew(VMTSound);
    sound->start_frame = p_start;
    sound->end_frame = p_end;
    sound->row = p_row;
    sound->refresh_position();
    return sound;
}

void VMTSound::refresh_position() {
    float zoom_factor = VisualMovieTab::get_singleton()->get_timeline()->get_zoom_factor();
    set_position(Vector2(start_frame * zoom_factor, NODE_HEIGHT + NODE_POS + (row * SOUND_HEIGHT)));
    set_size(Vector2(get_length() * zoom_factor, SOUND_HEIGHT));
}

int VMTSound::to_row(float p_height) const {
    return (p_height - NODE_HEIGHT - NODE_POS) / SOUND_HEIGHT;
}


