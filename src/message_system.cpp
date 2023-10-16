#include "message_system.hpp"
#include <map>

namespace MessageSystem {
    std::map<unsigned int, std::shared_ptr<Scene>> message_table;
}

void MessageSystem::registrScene(std::shared_ptr<Scene> scene, const unsigned int key)
{
    message_table.insert({key, scene});
}

void MessageSystem::unregistScene(const unsigned int key)
{
    message_table.erase(key);
}
