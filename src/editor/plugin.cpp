#include "plugin.h"

using namespace godot;

void CVMMPlugin::_bind_methods() {
}

CVMMPlugin::CVMMPlugin() {
}

CVMMPlugin::~CVMMPlugin() {
}

void CVMMPlugin::_enter_tree() {
    editor = EditorInterface::get_singleton();
    plugin_tab = memnew(VisualMovieTab);
    plugin_tab->set_name("CVMM");
    editor->get_editor_main_screen()->add_child(plugin_tab);
    plugin_tab->set_visible(false);
}

void CVMMPlugin::_exit_tree() {
    EditorInterface *editor = EditorInterface::get_singleton();
    Control *my_tab = static_cast<Control*>(editor->get_editor_main_screen()->find_child("MyTab", true, false));
    if (my_tab) {
        my_tab->queue_free();
    }
}

bool CVMMPlugin::_has_main_screen() const {
    return true;
}

String CVMMPlugin::_get_plugin_name() const {
    return "CVMM";
}

Ref<Texture2D> CVMMPlugin::_get_plugin_icon() const {
    return static_cast<Ref<Texture2D>>(ResourceLoader::get_singleton()->load("res://bin/assets/icon.png", "Texture2D"));
}

void CVMMPlugin::_make_visible(bool p_visible) {
    plugin_tab->set_visible(p_visible);
    plugin_tab->get_preview()->get_canvas_layer()->set_visible(p_visible);
    editor->get_base_control()->get_tree()->connect(
        "process_frame",
        Callable(plugin_tab->get_preview(), "update_svc"),
        Object::CONNECT_ONE_SHOT + Object::CONNECT_DEFERRED
    );
}
