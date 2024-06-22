#include "tab.h"

#define OUTER_MARGIN 3

using namespace godot;

VisualMovieTab *VisualMovieTab::singleton = nullptr;

void VisualMovieTab::_bind_methods() {
    ADD_SIGNAL(MethodInfo("movie_opened", PropertyInfo(Variant::STRING, "name")));
}

void VisualMovieTab::initialize_children() {
    VisualMovieTab::singleton = this;

    MarginContainer *margin_container = memnew(MarginContainer);
    margin_container->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin_container->begin_bulk_theme_override();
    margin_container->add_theme_constant_override("margin_left", OUTER_MARGIN);
    margin_container->add_theme_constant_override("margin_top", OUTER_MARGIN);
    margin_container->add_theme_constant_override("margin_right", OUTER_MARGIN);
    margin_container->add_theme_constant_override("margin_bottom", OUTER_MARGIN);
    margin_container->end_bulk_theme_override();
    add_child(margin_container);

    VBoxContainer *outer_container = memnew(VBoxContainer);
    outer_container->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    margin_container->add_child(outer_container);

    toolbar = memnew(VMTToolbar);
    outer_container->add_child(toolbar);

    VSplitContainer *vsc = memnew(VSplitContainer);
    vsc->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsc->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    outer_container->add_child(vsc);

    HSplitContainer *hsc1 = memnew(HSplitContainer);
    hsc1->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsc1->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsc->add_child(hsc1);

    HSplitContainer *hsc2 = memnew(HSplitContainer);
    hsc2->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsc2->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsc1->add_child(hsc2);

    script_list = memnew(VMTSceneList);
    hsc2->add_child(script_list);

    filter_list = memnew(VMTFilterList);
    hsc2->add_child(filter_list);

    preview = memnew(VMTPreview);
    hsc1->add_child(preview);

    timeline = memnew(VMTTimeline);
    timeline->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    timeline->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsc->call_deferred("add_child", timeline);
    // vsc->add_child(timeline);

    new_movie_popup = memnew(VMTNewMoviePopup);
    add_child(new_movie_popup);

    open_movie_popup = memnew(VMTOpenMoviePopup);
    add_child(open_movie_popup);

    settings_popup = memnew(VMTSettingsPopup);
    add_child(settings_popup);

    edit_tween_popup = memnew(VMTEditTweenPopup);
    add_child(edit_tween_popup);
}

VisualMovieTab::VisualMovieTab() {
    set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

    initialize_children();
}

VisualMovieTab::~VisualMovieTab() {
}

void VisualMovieTab::new_movie(const String name) {
    UtilityFunctions::print("Creating new movie: " + name);
    Ref<DirAccess> dir = DirAccess::open("user://cvmm");
    Error err = dir->make_dir(name);
    ERR_FAIL_COND_MSG(err != OK, "Failed to create directory for new movie.");

    Ref<ConfigFile> config = memnew(ConfigFile);
    config->set_value("general", "project_name", name);
    err = config->save("user://cvmm/" + name + "/project.cvmm");
    ERR_FAIL_COND_MSG(err != OK, "Failed to save initial project configuration file.");

    open_movie("user://cvmm/" + name + "/");
    UtilityFunctions::print("New movie created: " + name);
}

void VisualMovieTab::open_movie(const String path) {
    Ref<ConfigFile> config = memnew(ConfigFile);
    String pathNormalized = path.trim_suffix("project.cvmm"); // normalize path
    Error err = config->load(pathNormalized + String("project.cvmm"));
    ERR_FAIL_COND_MSG(err != OK, "Failed to load project configuration file " + pathNormalized + "project.cvmm");

    movie = Movie{config->get_value("general", "project_name"), pathNormalized};
    get_tree()->connect("process_frame", Callable(get_settings_popup(), "initialize_settings"), CONNECT_ONE_SHOT + CONNECT_DEFERRED);

    // emit_signal("movie_opened", movie.name);
}

