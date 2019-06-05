#pragma once

#include <string>

using namespace std;

class Composer{
public:
    virtual const char *composeSite(vector<string> messages) = 0;
    virtual string composeGetMessages(vector<string> messages) = 0;
    virtual string composeMessage(string msg) = 0;
    virtual const char *composeAdd(string msg, bool added) = 0;
    virtual const char *composeRemoved(string msg, bool removed) = 0;
    virtual ~Composer() {}
};