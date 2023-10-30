#pragma once
#include "subject.hpp"
#include "object.hpp"
#include <map>
#include <memory>

class Scene : public Object {
public:
    Scene()
        : Object(), observer(), subject() {}
    virtual ~Scene() = default;

    void proccessEvents() override;
    void update() override;
    void draw() const override;

    void subscripe(Observer &observer)
    { subject.attach(observer); }
protected:

    [[nodiscard]] unsigned int createTable();

    unsigned int insertObject(std::unique_ptr<Object> object, const unsigned int table_id);
    Object *getObject(const unsigned int table_id, const unsigned int object_id);
    void eraseObject(const unsigned int object_id, const unsigned int table_id);

    void setTableProccessing(const unsigned int table_id, const bool is_proccessed);
    void proccessTable(const unsigned int table_id);
    void updateTable(const unsigned int table_id);
    void drawTable(const unsigned int table_id) const;

    void clearTable(const unsigned int table_id);
protected:
    Observer observer {};
    Subject subject {};
private:
    using object_table = std::map<unsigned int, std::unique_ptr<Object>>;

    struct ObjectTable {
        object_table table {};
        bool isProccessed = false;
    };
    std::map<unsigned int, std::unique_ptr<ObjectTable>> tables {};
};
