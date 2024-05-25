#pragma once

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {

class VisualMovie : public Resource {
    GDCLASS(VisualMovie, Resource);

    private:

    protected:
        static void _bind_methods();

    public:
        VisualMovie();
        ~VisualMovie();

};

}