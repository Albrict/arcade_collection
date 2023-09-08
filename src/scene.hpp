#pragma once
#include "subject.hpp"

class Scene {
public:
    Scene()
        : observer(), subject() {}

    virtual ~Scene() {}

    virtual void proccessEvents() = 0;
    virtual void update() = 0;
    virtual void draw() noexcept = 0;

    void subscripe(Observer &observer)
    { subject.attach(observer); }
protected:
    Observer observer;
    Subject subject;
};
