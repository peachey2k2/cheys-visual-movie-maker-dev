#include "editor/lists.h"

#define OUTER_MARGIN 8

using namespace godot;

void VMTList::_bind_methods() {
}

VMTList::VMTList() {
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

    MarginContainer *margin = memnew(MarginContainer);
    margin->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->begin_bulk_theme_override();
    margin->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin->end_bulk_theme_override();
    add_child(margin);

    VBoxContainer *vbox = memnew(VBoxContainer);
    vbox->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->add_child(vbox);


    HBoxContainer *hotbar = memnew(HBoxContainer);
    hotbar->set_h_size_flags(SIZE_EXPAND_FILL);
    ADD_BUTTON(hotbar, New, "ScriptCreate");
    ADD_BUTTON(hotbar, Remove, "ScriptRemove");
    title = memnew(Label);
    title->set_horizontal_alignment(HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
    title->set_h_size_flags(SIZE_EXPAND_FILL);
    hotbar->add_child(title);
    vbox->add_child(hotbar);

    HBoxContainer *search = memnew(HBoxContainer);
    search->set_h_size_flags(SIZE_EXPAND_FILL);
    LineEdit *searchbar = memnew(LineEdit);
    searchbar->set_h_size_flags(SIZE_EXPAND_FILL);
    search->add_child(searchbar);
    ADD_BUTTON(search, Search, "Search");
    vbox->add_child(search);

    list = memnew(ItemList);
    list->set_h_size_flags(SIZE_EXPAND_FILL);
    list->set_v_size_flags(SIZE_EXPAND_FILL);
    list->add_item("Item 1");
    list->add_item("Item 2");
    list->add_item("Item 3");
    list->add_item("Item 4");
    list->add_item("Item 5");
    list->add_item("Item 6");
    list->add_item("Item 7");
    list->add_item("Item 8");
    list->add_item("Item 9");
    list->add_item("Item 10");
    vbox->add_child(list);
}

VMTList::~VMTList() {
}

void VMTScriptList::_bind_methods() {
}

VMTScriptList::VMTScriptList() {
    set_title("Scripts");
}

VMTScriptList::~VMTScriptList() {
}

void VMTFilterList::_bind_methods() {
}

VMTFilterList::VMTFilterList() {
    set_title("Filters");
}

VMTFilterList::~VMTFilterList() {
}



