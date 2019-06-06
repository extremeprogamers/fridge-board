#pragma once

#ifndef FRIDGE1_DATABASE_H
#define FRIDGE1_DATABASE_H

#include <string>
#include <vector>
#include "MessagesRepository.h"

class DatabaseRepository : public MessagesRepository {
private:
    std::vector<std::string> storage;

public:
bool add(std::string message) {
    storage.push_back(message);
    return true;
}

bool remove(int id) {
    storage.erase(storage.begin() + id);
    return true;
}

std::vector<std::string> getAll() {
    return storage;
}

bool clear() {
    storage.clear();
    return true;
}
};

#endif