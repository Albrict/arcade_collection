#include "message_system.hpp"
#include <any>
#include <map>
#include <memory>
#include <queue>
#include <cassert>

namespace MessageSystem {
    union message_type {
        std::any data;
        std::any *data_ptr;
        std::shared_ptr<std::any> data_shared_ptr;
    };

    struct Message {
        void *data = nullptr;
        std::any any_data {};
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

std::any MessageSystem::getMessage(const unsigned int object_id, unsigned int *sender)
{
    auto message_queue = message_table.find(object_id);
    assert(message_queue != message_table.end());
    if (!message_queue->second->empty()) {
        std::any message = message_queue->second->front().any_data; 
        if (sender)
            *sender = message_queue->second->front().sender;
        message_queue->second->pop();
        return message;
    }
    return std::any {};
}

void MessageSystem::sendMessage(const unsigned int object_id, std::any data, const unsigned int sender)
{
    auto message_queue = message_table.find(object_id);
    assert(message_queue != message_table.end());
    message_queue->second->push({nullptr, data, sender});
}
