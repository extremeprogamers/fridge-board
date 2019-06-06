#pragma once

#include <string>
#include <vector>

class Composer {
public:
    virtual const char *composeSite(std::vector<std::string> messages) = 0;
    virtual std::string composeGetMessages(std::vector<std::string> messages) = 0;
    virtual std::string composeMessage(std::string msg, int id) = 0;
    virtual ~Composer() {}
};