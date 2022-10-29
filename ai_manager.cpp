#include "ai_manager.h"

AIManager *AIManager::singleton = nullptr;

AIManager *AIManager::get_singleton() {
    return AIManager::singleton;
}

void AIManager::add(int p_value) {
    print_line("test...", p_value);
}

void AIManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("add", "value"), &AIManager::add);
}


AIManager::AIManager() {
    AIManager::singleton = this;;
}