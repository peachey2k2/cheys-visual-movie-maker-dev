#include "visual_movie_player.h"

using namespace godot;

void VisualMoviePlayer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_movie", "movie"), &VisualMoviePlayer::set_movie);
    ClassDB::bind_method(D_METHOD("get_movie"), &VisualMoviePlayer::get_movie);
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "movie", PROPERTY_HINT_RESOURCE_TYPE, "VisualMovie"), "set_movie", "get_movie");
}

VisualMoviePlayer::VisualMoviePlayer() {
}

VisualMoviePlayer::~VisualMoviePlayer() {
}

void VisualMoviePlayer::set_movie(VisualMovie *p_movie) {
    movie = p_movie;
}

VisualMovie *VisualMoviePlayer::get_movie() const {
    return movie;
}