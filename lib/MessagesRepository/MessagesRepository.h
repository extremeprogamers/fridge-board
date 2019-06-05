#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "Message.h"

using namespace std;

class MessagesRepository {
public:
    virtual bool add(string message) = 0;
    virtual bool remove(int id) = 0;
    virtual vector<string> getAll() = 0;
    virtual bool clear() = 0;    
    virtual ~MessagesRepository() {};
    
private:
    map<int, unique_ptr<Message>> storage;
    int max_id = 0;

};