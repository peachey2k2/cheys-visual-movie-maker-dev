#include "editor/lists.h"

using namespace godot;

void VMTList::_bind_methods() {
}

VMTList::VMTList() {
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

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
    add_child(list);
}

VMTList::~VMTList() {
}

void VMTScriptList::_bind_methods() {
}

VMTScriptList::VMTScriptList() {
}

VMTScriptList::~VMTScriptList() {
}

void VMTFilterList::_bind_methods() {
}

VMTFilterList::VMTFilterList() {
}

VMTFilterList::~VMTFilterList() {
}



