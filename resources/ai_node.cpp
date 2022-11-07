#include "ai_node.h"

struct AINodeComparator {
	_FORCE_INLINE_ bool operator()(const Ref<AINode> &a, const Ref<AINode> &b) const {
		return (a.ptr()->get_position().y < b.ptr()->get_position().y);
	}
};

void AINode::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_position"), &AINode::get_position);
	ClassDB::bind_method(D_METHOD("set_position", "position"), &AINode::set_position);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NO_EDITOR), "set_position", "get_position");
}

void AINode::set_position(Vector2 p_position) {
	position = p_position;
}

Vector2 AINode::get_position() const {
	return position;
}