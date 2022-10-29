#include "register_types.h"

#include "core/object/class_db.h"
#include "core/config/engine.h"

#include "ai_manager.h"

#ifdef TOOLS_ENABLED
#include "editor/ai_editor_plugin.h"
#endif

static AIManager *ai_manager = nullptr;

void initialize_ai_module(ModuleInitializationLevel p_level) {
	if (p_level == MODULE_INITIALIZATION_LEVEL_SERVERS) {
		ai_manager = memnew(AIManager);	
		GDREGISTER_CLASS(AIManager);
		Engine::get_singleton()->add_singleton(Engine::Singleton("AIManager", AIManager::get_singleton()));
	}

	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE) {
		// TODO
	}

#ifdef TOOLS_ENABLED
	if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR) {
		EditorPlugins::add_by_type<AIEditorPlugin>();
	}
#endif

}

void uninitialize_ai_module(ModuleInitializationLevel p_level) {
}
