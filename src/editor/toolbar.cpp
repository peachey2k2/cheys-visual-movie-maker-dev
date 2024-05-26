#include "editor/toolbar.h"

using namespace godot;

void VMTToolbar::_bind_methods() {
}

VMTToolbar::VMTToolbar() {
    set_custom_minimum_size(Size2(0, 24));

    add_child(create_button("File", {"New Movie", "Open", "Recent"}));
}

VMTToolbar::~VMTToolbar() {
}

MenuButton* VMTToolbar::create_button(const String &text, const std::vector<String> &items) {
    MenuButton *button = memnew(MenuButton);
    button->set_custom_minimum_size(Size2(0, 24));
    button->set_text(text);
    for (const String &item : items) {
        button->get_popup()->add_item(item);
    }
    return button;
}