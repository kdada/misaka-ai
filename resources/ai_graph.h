#ifndef AI_GRAPH_H
#define AI_GRAPH_H

#include "core/io/resource.h"

class AIGraph : public Resource {
    GDCLASS(AIGraph, Resource);
    OBJ_SAVE_TYPE(AIGraph);

    int root_node;

protected:
    static void _bind_methods();

public:
    int get_root_node();
    void set_root_node(int p_root_node);

};

#endif // AI_GRAPH_H