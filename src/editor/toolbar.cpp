#include "editor/toolbar.h"

#include "editor/tab.h"

using namespace godot;

void VMTToolbar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("menu_item_selected", "item_id"), &VMTToolbar::menu_item_selected);
}

VMTToolbar::VMTToolbar() {
    set_custom_minimum_size(Size2(0, 24));

    const std::vector<std::pair<String, std::vector<MenuItem>>> toolbar_items = {
        {"File", {
            MENU_ITEM("New Movie", DEFAULT),
            MENU_ITEM("Open", DEFAULT),
            MENU_ITEM("Recent", DEFAULT),
            MENU_ITEM("", SEPERATOR),
            MENU_ITEM("Save", DEFAULT),
            MENU_ITEM("Save As", DEFAULT),
            MENU_ITEM("Export", DEFAULT),
            MENU_ITEM("", SEPERATOR),
            MENU_ITEM("Settings", DEFAULT),
        }},
        {"Edit", {
            MENU_ITEM("Undo", DEFAULT),
            MENU_ITEM("Redo", DEFAULT),
            MENU_ITEM("", SEPERATOR),
            MENU_ITEM("Cut", DEFAULT),
            MENU_ITEM("Copy", DEFAULT),
            MENU_ITEM("Paste", DEFAULT),
            MENU_ITEM("", SEPERATOR),
            MENU_ITEM("Select All", DEFAULT),
        }},
        {"View", {
            MENU_ITEM("Zoom In", DEFAULT),
            MENU_ITEM("Zoom Out", DEFAULT),
            MENU_ITEM("", SEPERATOR),
            MENU_ITEM("Toggle Fullscreen", DEFAULT),
        }},
        {"Help", {
            MENU_ITEM("About", DEFAULT),
        }},
    };

    for (const auto [label, items] : toolbar_items) {
        PopupMenu *popup = create_button(label, items);
        popup->connect("id_pressed", Callable(this, "menu_item_selected"));
        add_child(popup);
    }
}

VMTToolbar::~VMTToolbar() {
}

PopupMenu* VMTToolbar::create_button(const String &menu_name, const std::vector<MenuItem> &items) {
    PopupMenu *popup = memnew(PopupMenu);
    popup->set_name(menu_name);
    for (const auto [label, type, hash] : items) {
        switch (type) {
            case SEPERATOR:
                popup->add_separator(label, hash);
                break;
            case DEFAULT:
                popup->add_item(label, hash);
                break;
            case CHECKABLE_CHECKBOX:
                popup->add_check_item(label, hash);
                break;
            case CHECKABLE_RADIO:
                popup->add_radio_check_item(label, hash);
                break;
            case SUBMENU:
                popup->add_submenu_item(label, "", hash);
                break;
        }
    }
    return popup;
}

void VMTToolbar::menu_item_selected(const uint item_id) {
    switch (item_id) {
        case "New Movie"_hash:
            break;
        case "Open"_hash:
            break;
        case "Recent"_hash:
            break;
        case "Save"_hash:
            break;
        case "Save As"_hash:
            break;
        case "Export"_hash:
            break;
        case "Settings"_hash:
            VisualMovieTab::get_singleton()->get_settings_popup()->popup_centered();
            break;
        case "Undo"_hash:
            break;
        case "Redo"_hash:
            break;
        case "Cut"_hash:
            break;
        case "Copy"_hash:
            break;
        case "Paste"_hash:
            break;
        case "Select All"_hash:
            break;
        case "Zoom In"_hash:
            break;
        case "Zoom Out"_hash:
            break;
        case "Toggle Fullscreen"_hash:
            break;
        case "About"_hash:
            break;
    }
}

