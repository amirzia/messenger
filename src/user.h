
#include <iostream>
#include <string>

using namespace std;

#ifndef H_USER
#define H_USER

struct User {
    User(string username);
    auto getUsername() -> string;

    private:
    const string username;
};

#endif