#include "popups/open.h"

#include "editor/tab.h"

using namespace godot;

void VMTOpenMoviePopup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("close_popup"), &VMTOpenMoviePopup::close_popup);
    ClassDB::bind_method(D_METHOD("_on_file_selected", "file"), &VMTOpenMoviePopup::_on_file_selected);
}

VMTOpenMoviePopup::VMTOpenMoviePopup() {
    hide();
    set_title("Open Movie");
    set_access(EditorFileDialog::ACCESS_FILESYSTEM);
    set_file_mode(EditorFileDialog::FILE_MODE_OPEN_FILE);
    set_current_dir(OS::get_singleton()->get_user_data_dir()); // for some reason "user://" didn't work
    set_filters({Array::make("*.cvmm; Visual Movie (*.cvmm)")});
    connect("file_selected", Callable(this, "_on_file_selected"));
    connect("close_requested", Callable(this, "close_popup"));
}

VMTOpenMoviePopup::~VMTOpenMoviePopup() {
}

void VMTOpenMoviePopup::_popup() {
    popup_centered(Size2(700, 500));
}

void VMTOpenMoviePopup::close_popup() {
    hide();
}

void VMTOpenMoviePopup::_on_file_selected(const String &file) {
    VisualMovieTab::get_singleton()->open_movie(file);
    close_popup();
}
