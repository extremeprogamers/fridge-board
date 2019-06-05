#pragma once

#ifndef FRIDGE1_ENDPOINT_DISPATCHER_H
#define FRIDGE1_ENDPOINT_DISPATCHER_H

#include <string>
#include <list>
#include "MessagesRepository.h"
#include "Composer.h"

using namespace std;

class EndpointDispatcher {
private:
    MessagesRepository *repository;
    Composer *composer;

public:
    EndpointDispatcher(MessagesRepository *db, Composer *comp) {
        this->repository = db;
        this->composer = comp;
    }
    const char *getMsgs() {
        vector<string> messages = this->repository->getAll();
        return this->composer->composeSite(messages);
    }

    void postMsg(string msg) {
        repository->add(msg);
    }

    void *deleteMsg(int id) {
        repository->remove(id);
    }
};

#endif
