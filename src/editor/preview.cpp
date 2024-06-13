#include "editor/preview.h"

#include <editor/tab.h>

#define OUTER_MARGIN 8

using namespace godot;

void VMTPreview::_bind_methods() {
    ClassDB::bind_method(D_METHOD("update_svc"), &VMTPreview::update_svc);
    ClassDB::bind_method(D_METHOD("_update_svc"), &VMTPreview::_update_svc);
    ClassDB::bind_method(D_METHOD("_on_movie_opened", "name"), &VMTPreview::_on_movie_opened);
}

void VMTPreview::_ready() {
    VisualMovieTab::get_singleton()->connect("movie_opened", Callable(this, "_on_movie_opened"));
}

VMTPreview::VMTPreview() {
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

    MarginContainer *margin = memnew(MarginContainer);
    margin->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->begin_bulk_theme_override();
    margin->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin->end_bulk_theme_override();
    add_child(margin);

    VBoxContainer *vbc = memnew(VBoxContainer);
    vbc->set_anchors_preset(Control::PRESET_FULL_RECT);
    // vbc->set_h_size_flags(SIZE_EXPAND_FILL);
    // vbc->set_v_size_flags(SIZE_EXPAND_FILL);
    margin->add_child(vbc);

    aspect_ratio_container = memnew(AspectRatioContainer);
    aspect_ratio_container->set_h_size_flags(SIZE_EXPAND_FILL);
    aspect_ratio_container->set_v_size_flags(SIZE_EXPAND_FILL);
    vbc->add_child(aspect_ratio_container);

    // Normally this would be a SubViewport, but those don't work with autoscaling.
    // Using a dummy Control and moving the SubViewportContainer to the parent seemed
    // to do the trick. This is a workaround for now. (now meeans ever)
    dummy = memnew(Control);
    dummy->set_h_size_flags(SIZE_EXPAND_FILL);
    dummy->set_v_size_flags(SIZE_EXPAND_FILL);
    aspect_ratio_container->add_child(dummy);

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

    HFlowContainer *buttons_container = memnew(HFlowContainer);
    buttons_container->set_h_size_flags(SIZE_EXPAND_FILL);
    buttons_container->set_alignment(HFlowContainer::ALIGNMENT_CENTER);
    ADD_BUTTON(buttons_container, play, "Play", "Play");
    ADD_BUTTON(buttons_container, pause, "Pause", "Pause");
    ADD_BUTTON(buttons_container, stop, "Stop", "Stop");
    vbc->add_child(buttons_container);

    connect("resized", Callable(this, "update_svc"));
}

VMTPreview::~VMTPreview() {
}

void VMTPreview::update_svc() {
    if (dummy->is_inside_tree()) {
        get_tree()->connect("process_frame", Callable(this, "_update_svc"), CONNECT_ONE_SHOT + CONNECT_REFERENCE_COUNTED);
    }
}

void VMTPreview::_update_svc() {
    svc->set_position(dummy->get_global_position());
    svc->set_scale(Vector2(1, 1) * dummy->get_size().x/svc->get_size().x);
}

void VMTPreview::_on_movie_opened(const String &name) {
    Vector2 dims = VisualMovieTab::get_singleton()->get_setting("general/viewport_dimensions");
    sub_viewport->set_size(dims);
    aspect_ratio_container->set_ratio(dims.x/dims.y);
    svc->set_size(dims);
    get_tree()->connect("process_frame", Callable(this, "update_svc"), CONNECT_ONE_SHOT + CONNECT_DEFERRED);
    update_svc();
}