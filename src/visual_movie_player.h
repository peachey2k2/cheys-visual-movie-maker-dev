#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/core/class_db.hpp>

#include "visual_movie.h"

namespace godot {

class VisualMoviePlayer : public Control {
    GDCLASS(VisualMoviePlayer, Control);

    private:
        VisualMovie *movie = nullptr;

    protected:
        static void _bind_methods();

    public:
        VisualMoviePlayer();
        ~VisualMoviePlayer();

        void set_movie(VisualMovie *p_movie);
        VisualMovie *get_movie() const;
};

}
