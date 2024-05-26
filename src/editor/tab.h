#pragma once

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/margin_container.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/scroll_container.hpp>
#include <godot_cpp/classes/h_split_container.hpp>
#include <godot_cpp/classes/v_split_container.hpp>
#include <godot_cpp/classes/item_list.hpp>

#include "editor/toolbar.h"

namespace godot {

class VisualMovieTab : public Control {
    GDCLASS(VisualMovieTab, Control);

    private:
        void initialize_children();

        // All the internal nodes. Indents are used to show the hierarchy.
        // Kepp in mind that not every node is a member field, so they're commented out.
        // MarginContainer *margin_container;
            // VBoxContainer *vbox_container;
                VMTToolbar *toolbar;
                    // Button *button1;
                    // Button *button2;
                    // Button *button3;
                // VSplitContainer *vsplit_container;
                    // HSplitContainer *hsplit_container;
                        VBoxContainer *script_list;
                            // ItemList *list;
                        VBoxContainer *filter_list;
                            // ItemList *list;
                        VBoxContainer *preview;
                    ScrollContainer *timeline;


    protected:
        static void _bind_methods();

    public:
        VisualMovieTab();
        ~VisualMovieTab();

};

}

