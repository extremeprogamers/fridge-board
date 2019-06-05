#pragma once

#ifndef FRIDGE1_DATABASE_H
#define FRIDGE1_DATABASE_H

#include <string>
#include <vector>
#include "MessagesRepository.h"
#include "Message.h"

using namespace std;

class DatabaseRepository : public MessagesRepository {
private:
    vector<string> storage;

public:
bool add(string message) {
    auto p = make_unique(MessagesRepository(message));
    storage.emplace(p->id, move(p));
    return true;
}

bool remove(int id) {
    storage.erase(id);
    return true;
}

vector<string> getAll() {
    return storage;
}

bool clear() {
    storage.clear();
    return true;
}
};

#endif