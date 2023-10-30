#include "scene.hpp"
#include <stdexcept>
#include <cassert>

void Scene::proccessEvents()
{
    for (auto &table : tables) {
        if (table.second->isProccessed) {
            for (auto &object : table.second->table)
                    object.second->proccessEvents(); 
        }
    }
}

void Scene::update()
{
    for (auto &table : tables) {
        if (table.second->isProccessed) {
            for (auto &object : table.second->table)
                    object.second->update(); 
        }
    }
}

void Scene::draw() const
{
    for (const auto &table : tables) {
        if (table.second->isProccessed) {
            for (const auto &object : table.second->table)
                    object.second->draw(); 
        }
    }
}

[[nodiscard]] unsigned int Scene::createTable()
{
    static unsigned int id_counter;
    ++id_counter;
    tables.insert({id_counter, std::make_unique<ObjectTable>()});
    return id_counter;
}


void Scene::setTableProccessing(const unsigned int table_id, const bool is_proccessed)
{
    auto table = tables.find(table_id);
    assert(table != tables.end());
    table->second->isProccessed = is_proccessed;
}

unsigned int Scene::insertObject(std::unique_ptr<Object> object, const unsigned int table_id)
{
    auto table = tables.find(table_id); 
    assert(table != tables.end());

    static unsigned int id_counter;
    ++id_counter;
    
    table->second->table.insert({id_counter, std::move(object)});
    return id_counter;
}

void Scene::eraseObject(const unsigned int object_id, const unsigned int table_id)
{
    auto table = tables.find(table_id);    
    assert(table != tables.end());
    table->second->table.erase(object_id);  
}

void Scene::proccessTable(const unsigned int table_id)
{
    auto table = tables.find(table_id);
    assert(table != tables.end());

    for (auto &object : table->second->table)
        object.second->proccessEvents();
}

void Scene::updateTable(const unsigned int table_id)
{
    auto table = tables.find(table_id);
    assert(table != tables.end());

    for (auto &object : table->second->table)
        object.second->update();
}

void Scene::drawTable(const unsigned int table_id) const 
{
    const auto table = tables.find(table_id);
    assert(table != tables.end());

    for (const auto &object : table->second->table)
        object.second->draw();
}

void Scene::clearTable(const unsigned int table_id)
{
    auto table = tables.find(table_id);
    if (table != tables.end())
        table->second->table.clear();    
    else
        return;
}
