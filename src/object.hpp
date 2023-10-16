#pragma once
#include <any>
#include <memory>
#include <map>

enum class Messages {
    START_GAME,
    EXIT_APP
};

class Object : std::enable_shared_from_this<Object> {
public:
    using shared_ptr = std::shared_ptr<Object>;    
    using shared_ptr_data = std::shared_ptr<std::any>;

    explicit Object();
    virtual ~Object() = default;
    
    virtual void proccessEvents() = 0;
    virtual void update() = 0;
    virtual void draw() const = 0;
    
    unsigned int getID() const noexcept
    { return object_id; }
    void addChild(shared_ptr object);
    void removeChild(const unsigned int id)
    { child_table->erase(id); }

    [[nodiscard]] bool sendMessageTo(const unsigned int to, shared_ptr_data data);
    [[nodiscard]] bool sendMessageTo(const unsigned int to, std::any data);
    
    void sendMessageToParent(shared_ptr_data data);
    void sendMessageToParent(std::any data);
    
    static void addObjectToGlobalTable(shared_ptr object);
    static shared_ptr getObjectFromGlobalTable();
protected:
    bool is_message_received;
private:
    using object_table = std::map<unsigned int, shared_ptr>;
    unsigned int object_id;
    std::unique_ptr<object_table> child_table;
    shared_ptr_data received_data;
    shared_ptr ptr_to_parent;
};
