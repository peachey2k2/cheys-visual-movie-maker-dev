#include "tab.h"

#define OUTER_MARGIN 3

using namespace godot;

void VisualMovieTab::_bind_methods() {
}

void VisualMovieTab::initialize_children() {
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

    script_list = memnew(VMTScriptList);
    hsc2->add_child(script_list);

    filter_list = memnew(VMTFilterList);
    hsc2->add_child(filter_list);

    preview = memnew(VMTPreview);
    hsc1->add_child(preview);

    timeline = memnew(ScrollContainer);
    timeline->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    timeline->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsc->add_child(timeline);
}

VisualMovieTab::VisualMovieTab() {
    set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

    initialize_children();
}

VisualMovieTab::~VisualMovieTab() {
}

VMTToolbar *VisualMovieTab::get_toolbar() {
    return toolbar;
}

VMTScriptList *VisualMovieTab::get_script_list() {
    return script_list;
}

VMTFilterList *VisualMovieTab::get_filter_list() {
    return filter_list;
}

VMTPreview *VisualMovieTab::get_preview() {
    return preview;
}

ScrollContainer *VisualMovieTab::get_timeline() {
    return timeline;
}

