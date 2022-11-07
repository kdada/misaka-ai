#ifndef AI_NODE_H
#define AI_NODE_H

#include "core/io/resource.h"
#include "core/templates/vector.h"

class AINode : public Resource {
	GDCLASS(AINode, Resource);
	OBJ_SAVE_TYPE(AINode);

	Vector2 position;

protected:
	static void _bind_methods();

public:
	void set_position(Vector2 p_position);
	Vector2 get_position() const;
};

#endif // AI_NODE_H