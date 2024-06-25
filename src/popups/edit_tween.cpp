#include "popups/edit_tween.h"

using namespace godot;

void VMTEditTweenPopup::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_save_pressed"), &VMTEditTweenPopup::_on_save_pressed);
    ClassDB::bind_method(D_METHOD("_on_cancel_pressed"), &VMTEditTweenPopup::_on_cancel_pressed);
    ClassDB::bind_method(D_METHOD("close_popup"), &VMTEditTweenPopup::close_popup);
}

VMTEditTweenPopup::VMTEditTweenPopup() {
    hide();
    connect("close_requested", Callable(this, "close_popup"));

    set_size(Size2(600, 800));
    set_title("Edit Tween");
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

    hbox = memnew(HBoxContainer);
    hbox->set_alignment(BoxContainer::ALIGNMENT_CENTER);
    vbox->add_child(hbox);

    Button *create = memnew(Button);
    create->connect("pressed", Callable(this, "_on_save_pressed"));
    create->set_text("Save");
    hbox->add_child(create);

    Button *cancel = memnew(Button);
    cancel->connect("pressed", Callable(this, "_on_cancel_pressed"));
    cancel->set_text("Cancel");
    hbox->add_child(cancel);
}

VMTEditTweenPopup::~VMTEditTweenPopup() {
}

void VMTEditTweenPopup::_popup(VMTTimelineItem *p_item) {
    popup_centered();
}

void VMTEditTweenPopup::close_popup() {
    queue_free();
}

void VMTEditTweenPopup::_on_save_pressed() {
}

void VMTEditTweenPopup::_on_cancel_pressed() {
    close_popup();
}

