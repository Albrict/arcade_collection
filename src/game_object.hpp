#pragma once
#include "object.hpp"
#include <raylib.h>

struct GameObject : public Object {
    GameObject(const Rectangle object_rect)
        : Object(), rect(object_rect) {}
    ~GameObject() = default;
public:
    Rectangle rect;
};
