#include "object.hpp"

namespace {
    std::map<unsigned int, Object::shared_ptr> global_object_table;
};
Object::Object()
    : is_message_received(false),
    child_table(),
    received_data(),
    ptr_to_parent()
{
    static unsigned int id_counter; 
    ++id_counter; 
    object_id = id_counter;
}

void Object::addChild(shared_ptr object)
{
    // If alreade have object table
    if (child_table) {
        child_table->insert({object->object_id, object});
        object->ptr_to_parent = shared_from_this(); 
    // Create it
    } else {
        child_table = std::make_unique<object_table>();
        // Put parent also into a table
        child_table->insert({object_id, shared_from_this()});
    }
}

[[nodiscard]] bool Object::sendMessageTo(const unsigned int to, shared_ptr_data data)
{
    auto iterator = ptr_to_parent->child_table->find(to);
    if (iterator != ptr_to_parent->child_table->end()) {
        shared_ptr object(iterator->second);
        object->received_data= data;
        object->is_message_received = true;
        return true;
    } else {
        return false;
    }
}

[[nodiscard]] bool Object::sendMessageTo(const unsigned int to, std::any data)
{
    auto iterator = ptr_to_parent->child_table->find(to);
    if (iterator != ptr_to_parent->child_table->end()) {
        shared_ptr object(iterator->second);
        *object->received_data = data;
        object->is_message_received = true;
        return true;
    } else {
        return false;
    }
}

void Object::sendMessageToParent(shared_ptr_data data)
{
    ptr_to_parent->received_data = data;
    ptr_to_parent->is_message_received = true;
}

void Object::sendMessageToParent(std::any data)
{
    *ptr_to_parent->received_data = data;
    ptr_to_parent->is_message_received = true;
}

void Object::addObjectToGlobalTable(shared_ptr object)
{
   global_object_table.insert({object->getID(), object});
}
