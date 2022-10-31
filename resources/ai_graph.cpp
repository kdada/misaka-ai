#include "ai_graph.h"

void AIGraph::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_root_node"), &AIGraph::get_root_node);
	ClassDB::bind_method(D_METHOD("set_root_node", "root_node"), &AIGraph::set_root_node);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "root_node", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_root_node", "get_root_node");
}

int AIGraph::get_root_node() {
    return root_node;
}

void AIGraph::set_root_node(int p_root_node) {
    root_node = p_root_node;
}