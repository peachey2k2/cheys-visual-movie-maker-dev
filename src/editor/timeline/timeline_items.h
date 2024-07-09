#pragma once

#include "godot_cpp/classes/button.hpp"
#include "godot_cpp/classes/editor_interface.hpp"
#include "godot_cpp/classes/style_box.hpp"
#include "godot_cpp/classes/input_event_mouse_button.hpp"

namespace godot {

class VMTTimelineItem : public Button {
    GDCLASS(VMTTimelineItem, Button);

    public:
        enum Direction {
            LEFT,
            RIGHT,
            MIDDLE,
        };

        typedef struct {
            VMTTimelineItem *item;
            Direction dir;
            float offset;
        } DragData;

    private:
        Control *l_handle;
        Control *r_handle;

    protected:
        static void _bind_methods();
        
        int start_frame;
        int end_frame;
        int row;

        void set_start_frame(int p_start);
        void set_end_frame(int p_end);
        void set_row(int p_row);
        virtual void double_clicked() {};

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
        void _on_gui_input_left(const InputEvent*);
        void _on_gui_input_right(const InputEvent*);
        void _on_gui_input_middle(const InputEvent*);

        static DragData cur_draggable;
        virtual void refresh_position() {};
        virtual int to_row(float p_height) const {return 0;};

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
        void double_clicked() override;

    public:
        VMTTween();
        ~VMTTween();
        static VMTTween *create(int p_start, int p_end, int p_row);
        int to_row(float p_height) const override;

};

class VMTNode : public VMTTimelineItem {
    GDCLASS(VMTNode, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

        void refresh_position() override;
        void double_clicked() override;

    public:
        VMTNode();
        ~VMTNode();
        static VMTNode *create(Node *p_root);
        int to_row(float p_height) const override;

};

class VMTSound : public VMTTimelineItem {
    GDCLASS(VMTSound, VMTTimelineItem);

    private:

    protected:
        static void _bind_methods();

        void refresh_position() override;
        void double_clicked() override;

    public:
        VMTSound();
        ~VMTSound();
        static VMTSound *create(int p_start, int p_end, int p_row);
        int to_row(float p_height) const override;

};

}