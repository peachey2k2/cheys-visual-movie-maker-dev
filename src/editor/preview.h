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

#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

class VMTPreview : public Panel {
    GDCLASS(VMTPreview, Panel);

    private:
        Control *dummy;
        SubViewport *sub_viewport;
        SubViewportContainer *svc;
        CanvasLayer *canvas_layer;
        HSlider *slider;


    protected:
        static void _bind_methods();

    public:
        VMTPreview();
        ~VMTPreview();

        void update_svc();

        CanvasLayer *get_canvas_layer();
        SubViewport *get_viewport();

};

}

