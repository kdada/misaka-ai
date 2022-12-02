#include "ai_editor_plugin.h"
#include "../resources/ai_graph.h"
#include "ai_graph_create_dialog.h"
#include "editor/editor_scale.h"
#include "scene/gui/split_container.h"
#include "scene/gui/menu_button.h"
#include "scene/gui/item_list.h"

void AIEditorPlugin::_bind_methods() {
}

bool AIEditorPlugin::handles(Object *p_object) const {
	return Object::cast_to<AIGraph>(p_object) != nullptr;
}

void AIEditorPlugin::_file_menu_item_pressed(int p_index) {
	switch (p_index) {
		case FILE_NEW:
			ai_graph_create_dialog->popup_centered();
			break;
		case FILE_SAVE: {
			Ref<AIGraph> ai_graph = ai_graphs[tab_container->get_current_tab()];
			ResourceSaver::save(ai_graph);
		} break;
		default:
			break;
	}
}

void AIEditorPlugin::_ai_graph_selected(int p_index) {
	// print_line("select ai graph", p_index);
}

void AIEditorPlugin::_ai_graph_clicked(int p_index, Vector2 p_local_mouse_pos, MouseButton p_mouse_button_index) {
	if (p_mouse_button_index == MouseButton::LEFT) {
		tab_container->set_current_tab(p_index);
	}
}

void AIEditorPlugin::_ai_graph_connection_request(StringName from_node, int from_port, StringName to_node, int to_port) {
	GraphEdit *graph_edit = Object::cast_to<GraphEdit>(tab_container->get_current_tab_control());
	print_line(graph_edit, from_node, from_port, to_node, to_port);
	graph_edit->connect_node(from_node, from_port, to_node, to_port);
}

void AIEditorPlugin::_ai_graph_disconnection_request(StringName from_node, int from_port, StringName to_node, int to_port) {
	GraphEdit *graph_edit = Object::cast_to<GraphEdit>(tab_container->get_current_tab_control());
	print_line(graph_edit, from_node, from_port, to_node, to_port);
	graph_edit->disconnect_node(from_node, from_port, to_node, to_port);
}

void AIEditorPlugin::_ai_graph_popup_request(Vector2 p_position) {
	ai_graph_create_node_dialog->popup_centered();
	latest_ai_graph_create_node_position = p_position;
}

void AIEditorPlugin::_ai_graph_create_node() {
	GraphEdit *graph_edit = Object::cast_to<GraphEdit>(tab_container->get_current_tab_control());
	Ref<AIGraph> ai_graph = ai_graphs[tab_container->get_current_tab()];

	Ref<AINode> ai_node = Ref<AINode>(memnew(AINode));
	ai_node->set_name("test");
	ai_node->set_position(latest_ai_graph_create_node_position);
	ai_graph->add_node(ai_node);
	if (ai_graph->get_root_node() == nullptr) {
		ai_graph->set_root_node(ai_node);
	}

	GraphNode *node = memnew(GraphNode);
	node->set_title("test");
	node->set_resizable(true);
	node->set_show_close_button(true);
	node->set_size(Size2(100, 100));
	node->set_name("test");
	node->add_child(memnew(Label("Internal")));
	node->set_slot(0, true, 0, Color(1, 1, 1, 1), true, 0, Color(0, 1, 0, 1));
	node->set_position_offset(latest_ai_graph_create_node_position);
	graph_edit->add_child(node);
}

void AIEditorPlugin::edit(Object *p_object) {
	EditorNode::get_singleton()->make_bottom_panel_item_visible(main_container);
	AIGraph *ai_graph = Object::cast_to<AIGraph>(p_object);
	for (int i = 0; i < ai_graphs.size(); i++) {
		if (ai_graph == ai_graphs[i].ptr()) {
			ai_graph_list->select(i);
			tab_container->set_current_tab(i);
			return;
		}
	}
	ai_graphs.push_back(Ref<AIGraph>(ai_graph));
	String path = ai_graph->get_path();
	String file = path.get_file();
	ai_graph_list->add_item(file);
	ai_graph_list->set_item_tooltip(ai_graph_list->get_item_count() - 1, path);
	ai_graph_list->select(ai_graphs.size() - 1);
	GraphEdit *graph_edit = memnew(GraphEdit);
	graph_edit->set_right_disconnects(true);
	graph_edit->connect("popup_request", callable_mp(this, &AIEditorPlugin::_ai_graph_popup_request));
	graph_edit->connect("connection_request", callable_mp(this, &AIEditorPlugin::_ai_graph_connection_request));
	graph_edit->connect("disconnection_request", callable_mp(this, &AIEditorPlugin::_ai_graph_disconnection_request));
	for (int i = 0; i < ai_graph->size(); i++) {
		Ref<AINode> ai_node = ai_graph->get_node(i);
		GraphNode *node = memnew(GraphNode);
		node->set_title(ai_node->get_name());
		node->set_resizable(true);
		node->set_show_close_button(true);
		node->set_size(Size2(100, 100));
		node->set_name(ai_node->get_name());
		node->add_child(memnew(Label("Internal")));
		node->set_slot(0, true, 0, Color(1, 1, 1, 1), true, 0, Color(0, 1, 0, 1));
		node->set_position_offset(ai_node->get_position());
		graph_edit->add_child(node);
	}
	tab_container->add_child(graph_edit);
	tab_container->set_current_tab(ai_graphs.size() - 1);
}

AIEditorPlugin::AIEditorPlugin() {
	main_container = memnew(HSplitContainer);

	VBoxContainer *left_sidebar = memnew(VBoxContainer);
	left_sidebar->set_custom_minimum_size(Size2(200, 300) * EDSCALE);

	HBoxContainer *menu_container = memnew(HBoxContainer);
	left_sidebar->add_child(menu_container);
	file_menu = memnew(MenuButton);
	file_menu->set_text("File");
	file_menu->get_popup()->add_item(TTR("New AI Graph"), FILE_NEW);
	file_menu->get_popup()->add_separator();
	file_menu->get_popup()->add_item(TTR("Load AI Graph File"), FILE_OPEN);
	file_menu->get_popup()->add_item(TTR("Save File"), FILE_SAVE);
	file_menu->get_popup()->add_item(TTR("Save File As"), FILE_SAVE_AS);
	file_menu->get_popup()->add_separator();
	file_menu->get_popup()->add_item(TTR("Close File"), FILE_CLOSE);
	file_menu->get_popup()->connect("id_pressed", callable_mp(this, &AIEditorPlugin::_file_menu_item_pressed));
	menu_container->add_child(file_menu);

	ai_graph_list = memnew(ItemList);
	ai_graph_list->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	ai_graph_list->connect("item_selected", callable_mp(this, &AIEditorPlugin::_ai_graph_selected));
	ai_graph_list->connect("item_clicked", callable_mp(this, &AIEditorPlugin::_ai_graph_clicked));
	ai_graph_list->set_drag_forwarding(this);
	left_sidebar->add_child(ai_graph_list);

	main_container->add_child(left_sidebar);

	tab_container = memnew(TabContainer);
	tab_container->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	tab_container->set_tabs_visible(false);

	main_container->add_child(tab_container);

	ai_graph_create_dialog = memnew(AIGraphCreateDialog);
	main_container->add_child(ai_graph_create_dialog);

	ai_graph_create_node_dialog = memnew(ConfirmationDialog);
	ai_graph_create_node_dialog->set_ok_button_text(TTR("Create"));
	ai_graph_create_node_dialog->set_title("Create AINode");
	ai_graph_create_node_dialog->get_ok_button()->connect("pressed", callable_mp(this, &AIEditorPlugin::_ai_graph_create_node));
	main_container->add_child(ai_graph_create_node_dialog);

	button = EditorNode::get_singleton()->add_bottom_panel_item(TTR("AI Editor"), main_container);
}