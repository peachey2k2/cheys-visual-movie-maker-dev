#pragma once

#include <godot_cpp/classes/aspect_ratio_container.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/sub_viewport_container.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/h_slider.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/color_rect.hpp>

namespace godot {

class VMTPreview : public Panel {
    GDCLASS(VMTPreview, Panel);

    private:
        AspectRatioContainer *aspect_ratio_container;
        ColorRect *dummy;
        SubViewport *sub_viewport;
        SubViewportContainer *svc;
        CanvasLayer *canvas_layer;
        HSlider *slider;


    protected:
        static void _bind_methods();

    public:
        VMTPreview();
        ~VMTPreview();

        void _ready() override;

        void update_svc();
        void _on_movie_opened(const String &name);

        CanvasLayer *get_canvas_layer() { return canvas_layer; }
        SubViewport *get_viewport() { return sub_viewport; }

};

}

