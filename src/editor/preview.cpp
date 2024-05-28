#include "editor/preview.h"

using namespace godot;

void VMTPreview::_bind_methods() {
    ClassDB::bind_method(D_METHOD("update_svc"), &VMTPreview::update_svc);
}

VMTPreview::VMTPreview() {
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

    VBoxContainer *vbc = memnew(VBoxContainer);
    vbc->set_anchors_preset(Control::PRESET_FULL_RECT);
    // vbc->set_h_size_flags(SIZE_EXPAND_FILL);
    // vbc->set_v_size_flags(SIZE_EXPAND_FILL);
    add_child(vbc);

    AspectRatioContainer *arc = memnew(AspectRatioContainer);
    arc->set_h_size_flags(SIZE_EXPAND_FILL);
    arc->set_v_size_flags(SIZE_EXPAND_FILL);
    vbc->add_child(arc);

    // Normally this would be a SubViewport, but those don't work with autoscaling.
    // Using a dummy Control and moving the SubViewportContainer to the parent seemed
    // to do the trick. This is a workaround for now. (now meeans ever)
    dummy = memnew(Control);
    dummy->set_h_size_flags(SIZE_EXPAND_FILL);
    dummy->set_v_size_flags(SIZE_EXPAND_FILL);
    arc->add_child(dummy);

    // CanvasLayer might not be necessary, but keeps things cleaner.
    canvas_layer = memnew(CanvasLayer);
    canvas_layer->set_layer(0);
    canvas_layer->set_visible(false);
    dummy->add_child(canvas_layer);

    svc = memnew(SubViewportContainer);
    svc->set_h_size_flags(SIZE_EXPAND_FILL);
    svc->set_v_size_flags(SIZE_EXPAND_FILL);
    canvas_layer->add_child(svc);

    sub_viewport = memnew(SubViewport);
    svc->add_child(sub_viewport);

    Sprite2D *sprite = memnew(Sprite2D);
    sprite->set_texture(Ref<Texture2D>(ResourceLoader::get_singleton()->load("res://icon.svg")));
    sprite->set_centered(false);
    sub_viewport->add_child(sprite);

    slider = memnew(HSlider);
    vbc->add_child(slider);

    connect("resized", Callable(this, "update_svc"));
}

VMTPreview::~VMTPreview() {
}

void VMTPreview::update_svc() {
    svc->set_position(dummy->get_global_position());
    // UtilityFunctions::print(canvas_layer->is_visible());
    svc->set_scale(Vector2(1, 1) * dummy->get_size().x/svc->get_size().x);
}

CanvasLayer *VMTPreview::get_canvas_layer() {
    return canvas_layer;
}

SubViewport *VMTPreview::get_viewport() {
    return sub_viewport;
}