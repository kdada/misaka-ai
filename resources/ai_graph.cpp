#include "ai_graph.h"

void AIGraph::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_root_node"), &AIGraph::get_root_node);
	ClassDB::bind_method(D_METHOD("set_root_node", "root_node"), &AIGraph::set_root_node);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "root_node", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_root_node", "get_root_node");

	ClassDB::bind_method(D_METHOD("get_nodes"), &AIGraph::get_nodes);
	ClassDB::bind_method(D_METHOD("set_nodes", "nodes"), &AIGraph::set_nodes);

	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "nodes", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_nodes", "get_nodes");
}

Ref<AINode> AIGraph::get_root_node() {
	return root_node;
}

void AIGraph::set_root_node(Ref<AINode> p_root_node) {
	root_node = p_root_node;
}

Array AIGraph::get_nodes() {
	return ai_nodes;
}

void AIGraph::set_nodes(Array p_nodes) {
	ai_nodes = p_nodes;
}

Ref<AINode> AIGraph::get_node(int p_index) {
	return ai_nodes[p_index];
}

void AIGraph::add_node(Ref<AINode> p_node) {
	ai_nodes.push_back(p_node);
}

int AIGraph::size() {
	return ai_nodes.size();
}