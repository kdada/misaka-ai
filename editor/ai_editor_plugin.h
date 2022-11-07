#ifndef AI_EDITOR_PLUGIN_H
#define AI_EDITOR_PLUGIN_H

#include "editor/editor_plugin.h"
#include "editor/editor_node.h"
#include "scene/gui/graph_edit.h"
#include "../resources/ai_graph.h"
#include "../resources/ai_node.h"

class AIGraphCreateDialog;
class GraphEdit;
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
	TabContainer *tab_container = nullptr;
	AIGraphCreateDialog *ai_graph_create_dialog = nullptr;
	ConfirmationDialog *ai_graph_create_node_dialog = nullptr;
	Vector2 latest_ai_graph_create_node_position;

	Vector<Ref<AIGraph>> ai_graphs;

	void _file_menu_item_pressed(int p_index);
	void _ai_graph_selected(int p_index);
	void _ai_graph_clicked(int p_item, Vector2 p_local_mouse_pos, MouseButton p_mouse_button_index);
	void _ai_graph_connection_request(StringName from_node, int from_port, StringName to_node, int to_port);
	void _ai_graph_disconnection_request(StringName from_node, int from_port, StringName to_node, int to_port);
	void _ai_graph_popup_request(Vector2 p_position);
	void _ai_graph_create_node();

protected:
	static void _bind_methods();

public:
	virtual bool handles(Object *p_object) const override;
	virtual void edit(Object *p_object) override;

	AIEditorPlugin();
};

#endif // AI_EDITOR_EDITOR_PLUGIN_H