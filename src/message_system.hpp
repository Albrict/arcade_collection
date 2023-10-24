#pragma once

#include <sched.h>
namespace MessageSystem {
    void registrObject(const unsigned int object_id);
    void unregistrObject(const unsigned int object_id);

    void *getMessage(const unsigned int object_id);
    void sendMessage(const unsigned int object_id, void *data);
};
