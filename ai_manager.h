#ifndef AI_MANAGER_H
#define AI_MANAGER_H

#include "core/object/ref_counted.h"

class AIManager: public Object {
    GDCLASS(AIManager, Object);

private:
    static AIManager *singleton;

protected:
    static void _bind_methods();

public:
    static AIManager *get_singleton();
    void add(int p_value);
    AIManager();
};

#endif // AI_MANAGER_H