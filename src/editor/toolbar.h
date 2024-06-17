#pragma once

#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/menu_button.hpp>
#include <godot_cpp/classes/menu_bar.hpp>
#include <godot_cpp/classes/popup_menu.hpp>
#include <godot_cpp/classes/label.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include "defines.h"

#define MENU_ITEM(m_name, m_type, m_flags) MenuItem{m_name, m_type, m_flags, m_name##_hash}

typedef struct {
    const char* name;
    int type;
    int flags;
    unsigned int hash;
} MenuItem;

namespace godot {

class VMTToolbar : public MenuBar {
    GDCLASS(VMTToolbar, MenuBar);

    enum {
        SEPERATOR,
        DEFAULT,
        CHECKABLE_CHECKBOX,
        CHECKABLE_RADIO,
        SUBMENU,
    };

    enum {
        REQUIRE_OPEN = 1 << 0,
    };

    private:
        PopupMenu* create_button(const String &menu_name, const std::vector<MenuItem> &items);
        void menu_item_selected(const unsigned int item_id);

        Label *label;

    protected:
        static void _bind_methods();

    public:
        VMTToolbar();
        ~VMTToolbar();

        void _on_movie_opened(const String &name);
        void _ready() override;
};

}
