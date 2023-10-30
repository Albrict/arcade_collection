#include "message_system.hpp"
#include <map>
#include <memory>
#include <queue>
#include <cassert>

namespace MessageSystem {
    struct Message {
        void *data;
        std::any any_data;
        const unsigned int sender;
    };

    std::map<unsigned int, std::unique_ptr<std::queue<Message>>> message_table;
}

void MessageSystem::registrObject(const unsigned int object_id)
{
    message_table.insert({object_id, std::make_unique<std::queue<Message>>()});
}

void MessageSystem::unregistrObject(const unsigned int object_id)
{
    message_table.erase(object_id);
}

void *MessageSystem::getMessage(const unsigned int object_id, unsigned int *sender)
{
    auto message_queue = message_table.find(object_id);
    void *message = nullptr; 
    assert(message_queue != message_table.end());
    if (!message_queue->second->empty()) {
        message = message_queue->second->front().data; 
        if (sender)
            *sender = message_queue->second->front().sender;
        message_queue->second->pop();
    }
    return message;
}

void MessageSystem::sendMessage(const unsigned int object_id, void *data, const unsigned int sender)
{
    auto message_queue = message_table.find(object_id);
    assert(message_queue != message_table.end());
    message_queue->second->push({data, sender});
}

void MessageSystem::sendMessage(const unsigned int object_id, std::any data, const unsigned int sender)
{
    auto message_queue = message_table.find(object_id);
    Message msg = {nullptr, {}, sender};

    assert(message_queue != message_table.end());
    msg.any_data = data;
    message_queue->second->push(msg);
}

std::any MessageSystem::getAnyMessage(const unsigned int object_id, unsigned int *sender)
{
    auto message_queue = message_table.find(object_id);
    std::any message = nullptr; 
    assert(message_queue != message_table.end());
    if (!message_queue->second->empty()) {
        message = message_queue->second->front().any_data; 
        if (sender)
            *sender = message_queue->second->front().sender;
        message_queue->second->pop();
    }
    return message;
}
