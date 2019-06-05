#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

using namespace std;

class Message {
  public:
    const int id;
    string message;
 
    Message(string m) :
        id(maxId++),
        message(m)
    {}
  private:
    static int maxId;
};

#endif