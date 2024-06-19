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
#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/config_file.hpp>

#include "editor/toolbar.h"
#include "editor/lists.h"
#include "editor/preview.h"
#include "editor/timeline/timeline.h"
#include "popups/new_movie.h"
#include "popups/open.h"
#include "popups/settings.h"

namespace godot {

class VisualMovieTab : public Control {
    GDCLASS(VisualMovieTab, Control);

    typedef struct {
        String name;
        String path;
    } Movie;

    private:
        void initialize_children();

        static VisualMovieTab *singleton;
        Movie movie;

        // All the internal nodes. Indents are used to show the hierarchy.
        // Kepp in mind that not every node is a member field, so they're commented out.

        // MarginContainer *margin_container;
            // VBoxContainer *vbox_container;
                VMTToolbar *toolbar;
                // VSplitContainer *vsplit_container;
                    // HSplitContainer *hsplit_container;
                        // HSplitContainer *hsplit_container;
                            VMTSceneList *script_list;
                            VMTFilterList *filter_list;
                        VMTPreview *preview;
                    VMTTimeline *timeline;
        VMTNewMoviePopup *new_movie_popup;
        VMTOpenMoviePopup *open_movie_popup;
        VMTSettingsPopup *settings_popup;


    protected:
        static void _bind_methods();

    public:
        VisualMovieTab();
        ~VisualMovieTab();

        static VisualMovieTab *get_singleton() { return singleton; };
        Movie *get_movie() { return &movie; }

        VMTToolbar *get_toolbar() { return toolbar; }
        VMTSceneList *get_script_list() { return script_list; }
        VMTFilterList *get_filter_list() { return filter_list; }
        VMTPreview *get_preview() { return preview; }
        VMTTimeline *get_timeline() { return timeline; }

        VMTNewMoviePopup *get_new_movie_popup() { return new_movie_popup; }
        VMTOpenMoviePopup *get_open_movie_popup() { return open_movie_popup; }
        VMTSettingsPopup *get_settings_popup() { return settings_popup; }

        Variant get_setting(const String p_name) { return settings_popup->get_setting(p_name); }

        void new_movie(const String name);
        void open_movie(const String path);

};

}

