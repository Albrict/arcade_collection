#pragma once
#include <any>

namespace MessageSystem {
    inline const unsigned int root_scene_id = 1;

    void registrObject(const unsigned int object_id);
    void unregistrObject(const unsigned int object_id);

    std::any getMessage(const unsigned int object_id, unsigned int *sender = nullptr);
    void sendMessage(const unsigned int object_id, std::any data, const unsigned int sender = 0);
};
