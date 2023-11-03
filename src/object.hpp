#pragma once
#include "message_system.hpp"

class Object {
public:
    explicit Object() 
    { static unsigned int id_counter; ++id_counter; object_id = id_counter; MessageSystem::registrObject(object_id); }
    virtual ~Object()
    { MessageSystem::unregistrObject(object_id); }
    virtual void proccessEvents() {} 
    virtual void update() {}
    virtual void draw() const {}
    
    unsigned int getObjectId() const noexcept
    { return object_id; }
    void setParentId(const unsigned int id) noexcept
    { parent_id = id; }
protected:
    unsigned int getParentId() const noexcept
    { return parent_id; }
protected:
    unsigned int object_id = 0;
private:
    unsigned int parent_id = 0;
};
