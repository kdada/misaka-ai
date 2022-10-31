#include "editor/editor_scale.h"

#include "../resources/ai_graph.h"
#include "ai_editor_plugin.h"

void AIEditorPlugin::_bind_methods() {
}

bool AIEditorPlugin::handles(Object *p_object) const {
	return Object::cast_to<AIGraph>(p_object) != nullptr;
}

void AIEditorPlugin::_file_menu_item_pressed(int p_index) {
    print_line("click menu", p_index);
}

void AIEditorPlugin::_ai_graph_selected(int p_index) {
    print_line("select ai graph", p_index);
}

void AIEditorPlugin::_ai_graph_clicked(int p_index, Vector2 p_local_mouse_pos, MouseButton p_mouse_button_index) {
    print_line("click ai graph", p_index);
    if (p_mouse_button_index == MouseButton::LEFT) {
        ai_graph_editor->set_visible(true);
    }
}

void AIEditorPlugin::edit(Object *p_object) {
    AIGraph *ai_graph = Object::cast_to<AIGraph>(p_object);
    ai_graph_list->add_item(ai_graph->get_path());
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

    PanelContainer *panel_container = memnew(PanelContainer);
    panel_container->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    ai_graph_editor = memnew(GraphEdit);
    ai_graph_editor->set_visible(false);
    panel_container->add_child(ai_graph_editor);

    main_container->add_child(panel_container);
    
    button = EditorNode::get_singleton()->add_bottom_panel_item(TTR("AI Editor"), main_container);
}