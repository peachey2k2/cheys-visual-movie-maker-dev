#include "editor/timeline/timeline_items.h"

#include "editor/tab.h"

using namespace godot;

/******* VMTTimeline methods *******/

void VMTTimelineItem::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_pressed"), &VMTTimelineItem::_on_pressed);
}

VMTTimelineItem::VMTTimelineItem() {
    l_handle = memnew(ColorRect);
    l_handle->set_custom_minimum_size(Size2(2, 0));
    l_handle->set_h_size_flags(Control::SIZE_SHRINK_BEGIN);
    l_handle->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    l_handle->set_default_cursor_shape(Control::CURSOR_HSIZE);
    add_child(l_handle);

    r_handle = memnew(ColorRect);
    r_handle->set_custom_minimum_size(Size2(2, 0));
    r_handle->set_h_size_flags(Control::SIZE_SHRINK_END);
    r_handle->set_v_size_flags(Control::SIZE_EXPAND_FILL);
    r_handle->set_default_cursor_shape(Control::CURSOR_HSIZE);
    add_child(r_handle);

    connect("pressed", Callable(this, "_on_pressed"));
    set_clip_text(true);
}

void VMTTimelineItem::_ready() {
    refresh_position();
}

VMTTimelineItem::~VMTTimelineItem() {
}

void VMTTimelineItem::_on_pressed() {
    UtilityFunctions::print(l_handle->get_position(), " ", r_handle->get_position());
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
    // ERR_FAIL_COND_MSG(p_end-p_start > get_length(), "Cannot resize to a length greater than the current length");
    set_start_frame(p_start);
    set_end_frame(p_end);
}

void VMTTimelineItem::move(int p_dest_frame, int p_dest_row) {
    start_frame = p_dest_frame;
    end_frame = p_dest_frame + get_length();
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


