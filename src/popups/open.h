#pragma once

#include <godot_cpp/classes/editor_file_dialog.hpp>
#include <godot_cpp/classes/os.hpp>

namespace godot {

class VMTOpenMoviePopup : public EditorFileDialog {
    GDCLASS(VMTOpenMoviePopup, EditorFileDialog);

    private:
    
    protected:
        static void _bind_methods();

    public:
        VMTOpenMoviePopup();
        ~VMTOpenMoviePopup();

        void _popup();
        void close_popup();
        void _on_file_selected(const String &file);
};

}