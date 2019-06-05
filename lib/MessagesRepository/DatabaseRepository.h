#pragma once

#ifndef FRIDGE1_DATABASE_H
#define FRIDGE1_DATABASE_H

#include <string>
#include <vector>
#include "MessagesRepository.h"

using namespace std;

class DatabaseRepository : public MessagesRepository {
private:
    vector<string> storage;

public:
bool add(string message) {
    storage.push_back(message);
    return true;
}

bool remove(string message) {
    storage.erase(storage.begin());
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