#pragma once

#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include "editor/tab.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

class CVMMPlugin : public EditorPlugin {
    GDCLASS(CVMMPlugin, EditorPlugin);

private:
    EditorInterface *editor = nullptr;
    VisualMovieTab *plugin_tab = nullptr;

protected:
    static void _bind_methods();

public:
    CVMMPlugin();
    ~CVMMPlugin();

    void _enter_tree() override;
    void _exit_tree() override;
    String _get_plugin_name() const override;
    Ref<Texture2D> _get_plugin_icon() const override;
    void _make_visible(bool p_visible) override;

    bool _has_main_screen() const;
};