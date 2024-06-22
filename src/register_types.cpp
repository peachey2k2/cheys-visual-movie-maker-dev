#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/editor_plugin_registration.hpp>

#include "visual_movie_player.h"
#include "visual_movie.h"
#include "editor/plugin.h"
#include "editor/tab.h"
#include "editor/toolbar.h"
#include "editor/lists.h"
#include "editor/preview.h"
#include "editor/timeline/timeline.h"
#include "editor/timeline/timeline_items.h"

#include "popups/new_movie.h"
#include "popups/open.h"
#include "popups/settings.h"

using namespace godot;

void initialize_gdextension_types(ModuleInitializationLevel p_level) {
	switch (p_level) {
	case MODULE_INITIALIZATION_LEVEL_SCENE:
		ClassDB::register_class<VisualMoviePlayer>();
		ClassDB::register_class<VisualMovie>();
		break;
		
	case MODULE_INITIALIZATION_LEVEL_EDITOR:
		// stuff related to editor tab plugin
		ClassDB::register_internal_class<CVMMPlugin>();
		EditorPlugins::add_by_type<CVMMPlugin>();
		ClassDB::register_internal_class<VisualMovieTab>();
		ClassDB::register_internal_class<VMTToolbar>();
		ClassDB::register_internal_class<VMTList>();
		ClassDB::register_internal_class<VMTSceneList>();
		ClassDB::register_internal_class<VMTFilterList>();
		ClassDB::register_internal_class<VMTPreview>();
		ClassDB::register_internal_class<VMTTimeline>();

		// timeline items
		ClassDB::register_abstract_class<VMTTimelineItem>();
		ClassDB::register_internal_class<VMTTween>();
		ClassDB::register_internal_class<VMTNode>();
		ClassDB::register_internal_class<VMTSound>();

		// popups for the tab plugin
		ClassDB::register_internal_class<VMTNewMoviePopup>();
		ClassDB::register_internal_class<VMTOpenMoviePopup>();
		ClassDB::register_internal_class<VMTSettingsPopup>();
		ClassDB::register_internal_class<VMTVector2Field>();
		ClassDB::register_internal_class<VMTEditTweenPopup>();
		break;
	}
}

void uninitialize_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
	// Initialization
	GDExtensionBool GDE_EXPORT cvmm_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_gdextension_types);
		init_obj.register_terminator(uninitialize_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}