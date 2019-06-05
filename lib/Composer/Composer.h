#pragma once

#include <string>
#include <vector>

using namespace std;

class Composer {
public:
    virtual const char *composeSite(vector<string> messages) = 0;
    virtual string composeGetMessages(vector<string> messages) = 0;
    virtual string composeMessage(string msg, int id) = 0;
    virtual ~Composer() {}
};