#pragma once

#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/editor_interface.hpp"
#include "godot_cpp/classes/style_box.hpp"

#include "godot_cpp/classes/color_rect.hpp"

namespace godot {

class VMTTimelineItem : public Button {
    GDCLASS(VMTTimelineItem, Button);

    private:
        ColorRect *l_handle;
        ColorRect *r_handle;

    protected:
        static void _bind_methods();
        
        int start_frame;
        int end_frame;
        int row;

        void set_start_frame(int p_start);
        void set_end_frame(int p_end);
        void set_row(int p_row);
        virtual void refresh_position() {};

    public:
        VMTTimelineItem();
        ~VMTTimelineItem();
        void _ready() override;

        int get_start_frame() const { return start_frame; }
        int get_end_frame() const { return end_frame; }
        int get_length() const { return end_frame - start_frame; }
        int get_row() const { return row; }

        void resize(int p_start, int p_end);
        void move(int p_dest_frame, int p_dest_row);

        void _on_pressed();

    public:
        static const int TWEEN_HEIGHT = 32;
        static const int NODE_HEIGHT  = 48;
        static const int SOUND_HEIGHT = 32;

        static const int NODE_POS = TWEEN_HEIGHT * 10;
        static const int TOTAL_HEIGHT = TWEEN_HEIGHT * 10 + NODE_HEIGHT + SOUND_HEIGHT * 10;

};

class VMTTween : public VMTTimelineItem {
    GDCLASS(VMTTween, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();
        void refresh_position() override;

    public:
        VMTTween();
        ~VMTTween();
        static VMTTween *create(int p_start, int p_end, int p_row);

};

class VMTNode : public VMTTimelineItem {
    GDCLASS(VMTNode, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

        void refresh_position() override;

    public:
        VMTNode();
        ~VMTNode();
        static VMTNode *create(Node *p_root);

};

class VMTSound : public VMTTimelineItem {
    GDCLASS(VMTSound, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

        void refresh_position() override;

    public:
        VMTSound();
        ~VMTSound();
        static VMTSound *create(int p_start, int p_end, int p_row);

};

}