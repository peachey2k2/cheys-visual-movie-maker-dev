#pragma once

#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/editor_interface.hpp"
#include "godot_cpp/classes/style_box.hpp"

namespace godot {

class VMTTimelineItem : public Button {
    GDCLASS(VMTTimelineItem, Button);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTTimelineItem();
        ~VMTTimelineItem();

};

class VMTTween : public VMTTimelineItem {
    GDCLASS(VMTTween, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTTween();
        ~VMTTween();

};

class VMTNode : public VMTTimelineItem {
    GDCLASS(VMTNode, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTNode();
        ~VMTNode();

};

class VMTSound : public VMTTimelineItem {
    GDCLASS(VMTSound, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTSound();
        ~VMTSound();

};

}