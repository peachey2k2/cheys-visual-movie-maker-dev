#pragma once

// include `editor_interface.hpp` and `button.hpp` from the Godot headers
#define ADD_BUTTON(m_parent, m_name, m_tooltip, m_icon)                                                            \
    Button *m_name = memnew(Button);                                                                    \
    m_name->add_theme_icon_override(                                                                    \
        "icon",                                                                                         \
        EditorInterface::get_singleton()->get_base_control()->get_theme_icon(m_icon, "EditorIcons")     \
    );                                                                                                  \
    m_name->set_tooltip_text(m_tooltip);                                                                \
    m_parent->add_child(m_name);

constexpr unsigned int operator "" _hash(const char* str, size_t length) {
    unsigned int hash = 0;
    for(size_t i = 0; i < length; ++i) {
        hash = 31 * hash + str[i];
    }
    return hash & 0x7FFFFFFF;
}