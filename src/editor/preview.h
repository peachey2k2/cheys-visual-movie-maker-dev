#pragma once

#include <godot_cpp/classes/aspect_ratio_container.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/sub_viewport_container.hpp>
#include <godot_cpp/classes/sub_viewport.hpp>

namespace godot {

class VMTPreview : public AspectRatioContainer {
    GDCLASS(VMTPreview, AspectRatioContainer);

    private:
        SubViewport *sub_viewport;
        SubViewportContainer *svc;
        CanvasLayer *canvas_layer;


    protected:
        static void _bind_methods();

    public:
        VMTPreview();
        ~VMTPreview();

        void update_svc();

        CanvasLayer *get_canvas_layer();

};

}

