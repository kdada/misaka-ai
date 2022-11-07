#ifndef AI_GRAPH_H
#define AI_GRAPH_H

#include "core/io/resource.h"
#include "core/variant/array.h"
#include "ai_node.h"

class AIGraph : public Resource {
    GDCLASS(AIGraph, Resource);
    OBJ_SAVE_TYPE(AIGraph);

    Ref<AINode> root_node;
    Array ai_nodes;

protected:
    static void _bind_methods();

public:
    Ref<AINode> get_root_node();
    void set_root_node(Ref<AINode> p_root_node);
    Array get_nodes();
    void set_nodes(Array p_nodes);
    Ref<AINode> get_node(int p_index);
    void add_node(Ref<AINode> p_node);
    int size();

};

#endif // AI_GRAPH_H