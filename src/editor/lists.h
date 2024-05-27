#pragma once

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/item_list.hpp>

namespace godot {

class VMTList : public VBoxContainer {
    GDCLASS(VMTList, VBoxContainer);

    private:
        ItemList *list;

    protected:
        static void _bind_methods();

    public:
        VMTList();
        ~VMTList();

};

class VMTScriptList : public VMTList {
    GDCLASS(VMTScriptList, VMTList);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTScriptList();
        ~VMTScriptList();

};

class VMTFilterList : public VMTList {
    GDCLASS(VMTFilterList, VMTList);

    private:

    protected:
        static void _bind_methods();

    public:
        VMTFilterList();
        ~VMTFilterList();

};

}