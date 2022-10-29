#include "editor/editor_scale.h"

#include "ai_editor_plugin.h"

void AIEditorPlugin::_bind_methods() {
}



bool AIEditorPlugin::handles(Object *p_object) const {
    return false;
}



AIEditorPlugin::AIEditorPlugin() {
    this->main_split = memnew(HSplitContainer);
    this->main_split->set_custom_minimum_size(Size2(200, 300) * EDSCALE);
    this->button = EditorNode::get_singleton()->add_bottom_panel_item(TTR("AI Editor"), main_split);
}