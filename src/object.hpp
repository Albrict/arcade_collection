#pragma once

class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void proccessEvents() = 0;
    virtual void update() = 0;
    virtual void draw() const  = 0;
};
