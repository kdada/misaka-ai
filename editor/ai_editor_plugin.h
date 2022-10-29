#ifndef AI_EDITOR_PLUGIN_H
#define AI_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "editor/editor_node.h"

class AIEditorPlugin : public EditorPlugin {
	GDCLASS(AIEditorPlugin, EditorPlugin);

private:
	HSplitContainer *main_split = nullptr;
	Button *button = nullptr;

protected:
	static void _bind_methods();

public:
	virtual bool handles(Object *p_object) const override;

	AIEditorPlugin();
};

#endif // AI_EDITOR_EDITOR_PLUGIN_H