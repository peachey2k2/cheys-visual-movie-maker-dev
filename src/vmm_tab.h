#pragma once

#include <godot_cpp/classes/control.hpp>

namespace godot {

class VisualMovieTab : public Control {
    GDCLASS(VisualMovieTab, Control);

    private:

    protected:
        static void _bind_methods();

    public:
        VisualMovieTab();
        ~VisualMovieTab();

};

}

