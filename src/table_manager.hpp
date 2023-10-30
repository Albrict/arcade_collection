#pragma once
#include "object.hpp"

class TableManager {
public:
    TableManager() = default;
    ~TableManager();
    
    unsigned int createTable();
    void addObject(std::shared_ptr<Object> object, const unsigned int table_id);
    void eraseObject(const unsigned int object_id, const unsigned int table_id);

    void focusTable(const unsigned int table_id);
    void unfocusTable(const unsigned int table_id);
};
