#include "message_system.hpp"
#include <map>
#include <memory>
#include <queue>
#include <cassert>

namespace MessageSystem {
    std::map<unsigned int, std::unique_ptr<std::queue<void*>>> message_table;
}

void MessageSystem::registrObject(const unsigned int object_id)
{
    message_table.insert({object_id, std::make_unique<std::queue<void*>>()});
}

void MessageSystem::unregistrObject(const unsigned int object_id)
{
    message_table.erase(object_id);
}

void *MessageSystem::getMessage(const unsigned int object_id)
{
    auto message_queue = message_table.find(object_id);
    void *message = nullptr; 
    assert(message_queue != message_table.end());
    if (!message_queue->second->empty()) {
        message = message_queue->second->front(); 
        message_queue->second->pop();
    }
    return message;
}

void MessageSystem::sendMessage(const unsigned int object_id, void *data)
{
    auto message_queue = message_table.find(object_id);
    assert(message_queue != message_table.end());
    message_queue->second->push(data);
}
