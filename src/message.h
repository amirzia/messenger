
#include <iostream>
#include <string>
#include <chrono>
#include "user.h"

using namespace std;

#ifndef H_MESSAGE
#define H_MESSAGE

struct Message {
    Message(User& from, User& to, string& content);

    private:
    const User from;
    const User to;
    const string content;
    const chrono::time_point<chrono::system_clock> sentTime;
};

#endif