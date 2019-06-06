#pragma once

#ifndef FRIDGE1_DATABASE_H
#define FRIDGE1_DATABASE_H

#include <string>
#include <vector>
#include "MessagesRepository.h"

class DatabaseRepository : public MessagesRepository {
private:
    std::map<int, std::string> storage;
    static int currentIndex;

public:
bool add(std::string message) {
    storage.emplace(currentIndex++, message);
    return true;
}

bool remove(int id) {
    storage.erase(id);
    return true;
}

std::map<int, std::string> getAll() {
    return storage;
}

bool clear() {
    storage.clear();
    return true;
}
};

#endif