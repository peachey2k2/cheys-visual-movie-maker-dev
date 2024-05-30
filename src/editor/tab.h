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
#include "editor/lists.h"
#include "editor/preview.h"
#include "popups/settings.h"

namespace godot {

class VisualMovieTab : public Control {
    GDCLASS(VisualMovieTab, Control);

    private:
        void initialize_children();

        static VisualMovieTab *singleton;

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
                        // HSplitContainer *hsplit_container;
                            VMTScriptList *script_list;
                            VMTFilterList *filter_list;
                        VMTPreview *preview;
                    ScrollContainer *timeline;
        VMTSettingsPopup *settings_popup;


    protected:
        static void _bind_methods();

    public:
        VisualMovieTab();
        ~VisualMovieTab();

        static VisualMovieTab *get_singleton() { return singleton; };

        VMTToolbar *get_toolbar() { return toolbar; }
        VMTScriptList *get_script_list() { return script_list; }
        VMTFilterList *get_filter_list() { return filter_list; }
        VMTPreview *get_preview() { return preview; }
        ScrollContainer *get_timeline() { return timeline; }
        VMTSettingsPopup *get_settings_popup() { return settings_popup; }

};

}

