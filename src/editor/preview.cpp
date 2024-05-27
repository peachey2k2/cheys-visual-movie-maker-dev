#include "editor/preview.h"

using namespace godot;

void VMTPreview::_bind_methods() {
    ClassDB::bind_method(D_METHOD("update_svc"), &VMTPreview::update_svc);
}

VMTPreview::VMTPreview() {
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

    // Normally this would be a SubViewport, but those don't work with autoscaling.
    // Using a dummy Control and moving the SubViewportContainer to the parent seemed
    // to do the trick. This is a workaround for now. (now meeans ever)
    Control *dummy = memnew(Control);
    dummy->set_h_size_flags(SIZE_EXPAND_FILL);
    dummy->set_v_size_flags(SIZE_EXPAND_FILL);
    add_child(dummy);

    // CanvasLayer might not be necessary, but keeps things cleaner.
    canvas_layer = memnew(CanvasLayer);
    canvas_layer->set_layer(0);
    canvas_layer->set_visible(false);
    dummy->add_child(canvas_layer);

    svc = memnew(SubViewportContainer);
    svc->set_h_size_flags(SIZE_EXPAND_FILL);
    svc->set_v_size_flags(SIZE_EXPAND_FILL);
    canvas_layer->add_child(svc);

    SubViewport *sub_viewport = memnew(SubViewport);
    svc->add_child(sub_viewport);

    connect("resized", Callable(this, "update_svc"));
}

VMTPreview::~VMTPreview() {
}

void VMTPreview::update_svc() {
    svc->set_position(get_global_position());
    svc->set_scale(Vector2(1, 1) * get_size()/svc->get_size());
}

CanvasLayer *VMTPreview::get_canvas_layer() {
    return canvas_layer;
}