#pragma once

#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/menu_button.hpp>
#include <godot_cpp/classes/menu_bar.hpp>
#include <godot_cpp/classes/popup_menu.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

constexpr unsigned int operator "" _hash(const char* str, size_t length) {
    unsigned int hash = 0;
    for(size_t i = 0; i < length; ++i) {
        hash = 31 * hash + str[i];
    }
    return hash & 0x7FFFFFFF;
}

#define MENU_ITEM(m_name, m_type) MenuItem{m_name, m_type, m_name##_hash}

typedef struct {
    const char* name;
    int type;
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

    private:
        PopupMenu* create_button(const String &menu_name, const std::vector<MenuItem> &items);
        void menu_item_selected(const uint item_id);

    protected:
        static void _bind_methods();

    public:
        VMTToolbar();
        ~VMTToolbar();

};

}
