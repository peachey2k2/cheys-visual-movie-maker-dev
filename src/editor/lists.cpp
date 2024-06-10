#include "editor/lists.h"

#include "editor/tab.h"
#include <functional>

#define OUTER_MARGIN 8

using namespace godot;

void VMTList::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_on_movie_opened", "name"), &VMTList::_on_movie_opened);
    ClassDB::bind_method(D_METHOD("update_files"), &VMTList::update_files);
}

void VMTList::_ready() {
    VisualMovieTab::get_singleton()->connect("movie_opened", Callable(this, "_on_movie_opened"));
    get_tree()->get_root()->connect("focus_entered", Callable(this, "update_files"));
}

VMTList::VMTList() {
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

    MarginContainer *margin = memnew(MarginContainer);
    margin->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->begin_bulk_theme_override();
    margin->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin->end_bulk_theme_override();
    add_child(margin);

    VBoxContainer *vbox = memnew(VBoxContainer);
    vbox->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin->add_child(vbox);


    HBoxContainer *hotbar = memnew(HBoxContainer);
    hotbar->set_h_size_flags(SIZE_EXPAND_FILL);
    ADD_BUTTON(hotbar, new_script, "New Script", "ScriptCreate");
    ADD_BUTTON(hotbar, nemove_script, "Remove Script", "ScriptRemove");
    ADD_BUTTON(hotbar, new_folder, "New Folder", "FolderCreate");
    ADD_BUTTON(hotbar, remove_folder, "Remove Folder", "Folder");
    ADD_BUTTON(hotbar, rename, "Rename", "Rename");
    title = memnew(Label);
    title->set_horizontal_alignment(HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
    title->set_h_size_flags(SIZE_EXPAND_FILL);
    hotbar->add_child(title);
    vbox->add_child(hotbar);

    HBoxContainer *search = memnew(HBoxContainer);
    search->set_h_size_flags(SIZE_EXPAND_FILL);
    LineEdit *searchbar = memnew(LineEdit);
    searchbar->set_h_size_flags(SIZE_EXPAND_FILL);
    searchbar->add_theme_stylebox_override("normal", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("panel", "Tree"));
    search->add_child(searchbar);
    ADD_BUTTON(search, Search, "Search", "Search");
    vbox->add_child(search);

    list = memnew(Tree);
    list->set_h_size_flags(SIZE_EXPAND_FILL);
    list->set_v_size_flags(SIZE_EXPAND_FILL);
    list->add_theme_stylebox_override("panel", EditorInterface::get_singleton()->get_base_control()->get_theme_stylebox("panel", "Tree"));
    
    vbox->add_child(list);
}

void VMTList::set_directory(const String &p_directory) {
    if (!DirAccess::dir_exists_absolute(p_directory)){
        DirAccess::make_dir_absolute(p_directory);
    }
    Ref<DirAccess> _dir = DirAccess::open(p_directory);
    ERR_FAIL_COND_MSG(_dir == nullptr, "Could not open directory: " + p_directory);
    dir = p_directory;
    update_files();
}

void VMTList::update_files() {
    if (VisualMovieTab::get_singleton()->get_movie() != nullptr) {
        list->clear();
        TreeItem *root = list->create_item();
        list->set_hide_root(true);
        if (dir != "") {
            static std::function<void(String, TreeItem*)> rec = [&](String path, TreeItem *parent) {
                for (auto dir : DirAccess::get_directories_at(path)){
                    TreeItem *item = list->create_item(parent);
                    item->set_text(0, dir);
                    item->set_icon(0, get_theme_icon("Folder", "EditorIcons"));
                    item->set_icon_modulate(0, EditorInterface::get_singleton()->get_editor_settings()->get("interface/theme/accent_color"));
                    rec(path + "/" + dir, item);
                }
                for (auto file : DirAccess::get_files_at(path)){
                    TreeItem *item = list->create_item(parent);
                    item->set_text(0, file);
                    item->set_icon(0, get_theme_icon("Script", "EditorIcons"));
                }
            };
            rec(dir, root);
        }
    }
}

VMTList::~VMTList() {
}

void VMTScriptList::_bind_methods() {
}

VMTScriptList::VMTScriptList() {
    set_title("Scripts");
}

void VMTScriptList::_on_movie_opened(const String &name) {
    set_directory(VisualMovieTab::get_singleton()->get_movie()->path + "/scripts");
}

VMTScriptList::~VMTScriptList() {
}

void VMTFilterList::_bind_methods() {
}

VMTFilterList::VMTFilterList() {
    set_title("Filters");
}

void VMTFilterList::_on_movie_opened(const String &name) {
    set_directory(VisualMovieTab::get_singleton()->get_movie()->path + "/filters");
}

VMTFilterList::~VMTFilterList() {
}



