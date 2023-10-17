#pragma once
#include "subject.hpp"
#include "object.hpp"

class Scene : public Object {
public:
    Scene()
        : observer(), subject() {}
    virtual ~Scene() = default;

    void subscripe(Observer &observer)
    { subject.attach(observer); }
protected:
    Observer observer;
    Subject subject;
};
