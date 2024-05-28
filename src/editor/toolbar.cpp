#include "editor/toolbar.h"

enum {
    SEPERATOR = -1,
    DEFAULT = 0,
    CHECKABLE_CHECKBOX = 1,
    CHECKABLE_RADIO = 2,
    SUBMENU = 3,
};

using namespace godot;

void VMTToolbar::_bind_methods() {
}

VMTToolbar::VMTToolbar() {
    set_custom_minimum_size(Size2(0, 24));

    add_child(create_button("File", {
        {"New Movie", DEFAULT},
        {"Open", DEFAULT},
        {"Recent", DEFAULT},
        {"", SEPERATOR},
        {"Save", DEFAULT},
        {"Save As", DEFAULT},
        {"Export", DEFAULT},
        {"", SEPERATOR},
        {"Settings", DEFAULT},
    }));
}

VMTToolbar::~VMTToolbar() {
}

MenuButton* VMTToolbar::create_button(const String &text, const std::vector<std::pair<String, int>> &items) {
    MenuButton *button = memnew(MenuButton);
    button->set_custom_minimum_size(Size2(0, 24));
    button->set_text(text);
    for (const auto &item : items) {
        switch (item.second) {
            case SEPERATOR:
                button->get_popup()->add_separator();
                break;
            case DEFAULT:
                button->get_popup()->add_item(item.first);
                break;
            case CHECKABLE_CHECKBOX:
                button->get_popup()->add_check_item(item.first);
                break;
            case CHECKABLE_RADIO:
                button->get_popup()->add_radio_check_item(item.first);
                break;
            case SUBMENU:
                button->get_popup()->add_submenu_item(item.first, "");
                break;
        }
    }
    return button;
}