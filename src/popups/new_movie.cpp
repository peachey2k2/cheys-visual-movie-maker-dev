#include "popups/new_movie.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include "editor/tab.h"

#include <godot_cpp/classes/editor_interface.hpp>

using namespace godot;

void VMTNewMoviePopup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("close_popup"), &VMTNewMoviePopup::close_popup);
    ClassDB::bind_method(D_METHOD("_on_create_pressed"), &VMTNewMoviePopup::_on_create_pressed);
    ClassDB::bind_method(D_METHOD("_on_cancel_pressed"), &VMTNewMoviePopup::_on_cancel_pressed);
}

void VMTNewMoviePopup::_on_create_pressed() {
    VisualMovieTab::get_singleton()->new_movie(name_input->get_text());
    close_popup();
}

void VMTNewMoviePopup::_on_cancel_pressed() {
    close_popup();
}

VMTNewMoviePopup::VMTNewMoviePopup() {
    hide();
    connect("close_requested", Callable(this, "close_popup"));

    set_size(Size2(300, 80));
    set_title("New Movie");
    set_flag(Window::FLAG_RESIZE_DISABLED, true);
    set_flag(Window::FLAG_ALWAYS_ON_TOP, false);

    Panel *panel = memnew(Panel);
    panel->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    Ref<StyleBox> style = EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("panel", "AcceptDialog");
    panel->add_theme_stylebox_override("panel", style);
    add_child(panel);

    VBoxContainer *vbox = memnew(VBoxContainer);
    vbox->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    vbox->set_alignment(BoxContainer::ALIGNMENT_CENTER);
    add_child(vbox);

    HBoxContainer *hbox = memnew(HBoxContainer);
    hbox->set_alignment(BoxContainer::ALIGNMENT_CENTER);
    vbox->add_child(hbox);

    Label *label = memnew(Label);
    label->set_text("Name:");
    hbox->add_child(label);

    name_input = memnew(LineEdit);
    name_input->set_custom_minimum_size(Size2(200, 0));
    hbox->add_child(name_input);

    hbox = memnew(HBoxContainer);
    hbox->set_alignment(BoxContainer::ALIGNMENT_CENTER);
    vbox->add_child(hbox);

    Button *create = memnew(Button);
    create->connect("pressed", Callable(this, "_on_create_pressed"));
    create->set_text("Create");
    hbox->add_child(create);

    Button *cancel = memnew(Button);
    cancel->connect("pressed", Callable(this, "_on_cancel_pressed"));
    cancel->set_text("Cancel");
    hbox->add_child(cancel);
}

VMTNewMoviePopup::~VMTNewMoviePopup() {
}

void VMTNewMoviePopup::_popup() {
    popup_centered();
    name_input->grab_focus();
}

void VMTNewMoviePopup::close_popup() {
    hide();
    name_input->clear();
}

