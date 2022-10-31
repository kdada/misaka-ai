#ifndef AI_EDITOR_PLUGIN_H
#define AI_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "editor/editor_node.h"
#include "scene/gui/graph_edit.h"

class AIEditorPlugin : public EditorPlugin {
	GDCLASS(AIEditorPlugin, EditorPlugin);

	enum {
		FILE_NEW,
		FILE_OPEN,
		FILE_SAVE,
		FILE_SAVE_AS,
		FILE_CLOSE
	};

	HSplitContainer *main_container = nullptr;
	Button *button = nullptr;
	MenuButton *file_menu = nullptr;
	ItemList *ai_graph_list = nullptr;
	GraphEdit *ai_graph_editor = nullptr;

	void _file_menu_item_pressed(int p_index);
	void _ai_graph_selected(int p_index);
	void _ai_graph_clicked(int p_item, Vector2 p_local_mouse_pos, MouseButton p_mouse_button_index);

protected:
	static void _bind_methods();

public:
	virtual bool handles(Object *p_object) const override;
	virtual void edit(Object *p_object) override;

	AIEditorPlugin();
};

#endif // AI_EDITOR_EDITOR_PLUGIN_H