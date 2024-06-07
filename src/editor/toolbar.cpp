#include "editor/toolbar.h"

#include "editor/tab.h"

using namespace godot;

void VMTToolbar::_bind_methods() {
    ClassDB::bind_method(D_METHOD("menu_item_selected", "item_id"), &VMTToolbar::menu_item_selected);
    ClassDB::bind_method(D_METHOD("_on_movie_opened", "name"), &VMTToolbar::_on_movie_opened);
}

void VMTToolbar::_ready() {
    VisualMovieTab::get_singleton()->connect("movie_opened", Callable(this, "_on_movie_opened"));
}

VMTToolbar::VMTToolbar() {
    set_custom_minimum_size(Size2(0, 24));

    const std::vector<std::pair<String, std::vector<MenuItem>>> toolbar_items = {
        {"File", {
            MENU_ITEM("New Movie", DEFAULT, 0),
            MENU_ITEM("Open", DEFAULT, 0),
            MENU_ITEM("Recent", DEFAULT, 0),
            MENU_ITEM("", SEPERATOR, REQUIRE_OPEN),
            MENU_ITEM("Save", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("Save As", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("Export", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("", SEPERATOR, REQUIRE_OPEN),
            MENU_ITEM("Settings", DEFAULT, REQUIRE_OPEN),
        }},
        {"Edit", {
            MENU_ITEM("Undo", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("Redo", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("", SEPERATOR, REQUIRE_OPEN),
            MENU_ITEM("Cut", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("Copy", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("Paste", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("", SEPERATOR, REQUIRE_OPEN),
            MENU_ITEM("Select All", DEFAULT, REQUIRE_OPEN),
        }},
        {"View", {
            MENU_ITEM("Zoom In", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("Zoom Out", DEFAULT, REQUIRE_OPEN),
            MENU_ITEM("", SEPERATOR, 0),
            MENU_ITEM("Toggle Fullscreen", DEFAULT, 0),
        }},
        {"Help", {
            MENU_ITEM("About", DEFAULT, 0),
        }},
    };

    for (const auto [label, items] : toolbar_items) {
        PopupMenu *popup = create_button(label, items);
        popup->connect("id_pressed", Callable(this, "menu_item_selected"));
        add_child(popup);
    }

    label = memnew(Label);
    label->set_text("No file opened");
    label->set_horizontal_alignment(HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
    label->set_anchors_and_offsets_preset(Control::PRESET_CENTER_RIGHT);
    add_child(label);
}

VMTToolbar::~VMTToolbar() {
}

PopupMenu* VMTToolbar::create_button(const String &menu_name, const std::vector<MenuItem> &items) {
    PopupMenu *popup = memnew(PopupMenu);
    popup->set_name(menu_name);
    for (const auto [label, type, flags, hash] : items) {
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
        if (flags & REQUIRE_OPEN) {
            popup->set_item_disabled(-1, true);
        }
    }
    return popup;
}

void VMTToolbar::menu_item_selected(const unsigned int item_id) {
    switch (item_id) {
        case "New Movie"_hash:
            VisualMovieTab::get_singleton()->get_new_movie_popup()->_popup();
            break;
        case "Open"_hash:
            VisualMovieTab::get_singleton()->get_open_movie_popup()->_popup();
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
            VisualMovieTab::get_singleton()->get_settings_popup()->_popup();
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

void VMTToolbar::_on_movie_opened(const String &name) {
    label->set_text(name);
    for (int i = 0; i < get_child_count(); i++) {
        PopupMenu *popup = Object::cast_to<PopupMenu>(get_child(i));
        if (popup) {
            for (int j = 0; j < popup->get_item_count(); j++) {
                popup->set_item_disabled(j, false);
            }
        }
    }
}

