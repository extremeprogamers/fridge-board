#pragma once

class MessagesRepository {
public:
    virtual bool add(std::string message) = 0;
    virtual bool remove(int id) = 0;
    virtual std::map<int, std::string> getAll() = 0;
    virtual bool clear() = 0;    
    virtual ~MessagesRepository() {}
};