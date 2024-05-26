#include "tab.h"

using namespace godot;

void VisualMovieTab::_bind_methods() {
}

void VisualMovieTab::initialize_children() {
    VBoxContainer *outer_container = memnew(VBoxContainer);
    outer_container->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);
    add_child(outer_container);

    toolbar = memnew(HFlowContainer);
    toolbar->set_custom_minimum_size(Size2(0, 32));
    outer_container->add_child(toolbar);

    Button *button1 = memnew(Button);
    Button *button2 = memnew(Button);
    Button *button3 = memnew(Button);
    toolbar->add_child(button1);
    toolbar->add_child(button2);
    toolbar->add_child(button3);

    VSplitContainer *vsplit_container = memnew(VSplitContainer);
    vsplit_container->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsplit_container->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    outer_container->add_child(vsplit_container);

    HSplitContainer *hsplit_container = memnew(HSplitContainer);
    hsplit_container->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsplit_container->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsplit_container->add_child(hsplit_container);

    script_list = memnew(VBoxContainer);
    script_list->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    script_list->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsplit_container->add_child(script_list);
    ItemList *list1 = memnew(ItemList);
    script_list->add_child(list1);

    filter_list = memnew(VBoxContainer);
    filter_list->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    filter_list->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsplit_container->add_child(filter_list);
    ItemList *list2 = memnew(ItemList);
    filter_list->add_child(list2);

    preview = memnew(VBoxContainer);
    preview->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    preview->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    hsplit_container->add_child(preview);

    timeline = memnew(ScrollContainer);
    timeline->set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    timeline->set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    vsplit_container->add_child(timeline);
}

VisualMovieTab::VisualMovieTab() {
    set_h_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    set_v_size_flags(SizeFlags::SIZE_EXPAND_FILL);
    set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

    initialize_children();
}

VisualMovieTab::~VisualMovieTab() {
}