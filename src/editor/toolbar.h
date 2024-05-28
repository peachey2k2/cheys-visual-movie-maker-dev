#pragma once

#include <godot_cpp/classes/h_flow_container.hpp>
#include <godot_cpp/classes/menu_button.hpp>
#include <godot_cpp/classes/popup_menu.hpp>

namespace godot {

class VMTToolbar : public HFlowContainer {
    GDCLASS(VMTToolbar, HFlowContainer);

    private:
        void initialize_children();

        MenuButton* create_button(const String &text, const std::vector<std::pair<String, int>> &items);

    protected:
        static void _bind_methods();

    public:
        VMTToolbar();
        ~VMTToolbar();

};

}