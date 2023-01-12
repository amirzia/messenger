
#include <iostream>
#include <string>

using namespace std;

#ifndef H_USER
#define H_USER

struct User {
    User() = default;
    User(string username);
    auto getUsername() const -> string;
    bool operator==(const User& u1) const {
        return username == u1.username;
    }
    private:
    string username;
};

namespace std {
    template <>
    struct hash<User> {
        std::size_t operator()(const User& u) {
            return hash<std::string>()(u.getUsername());
        }
    };
};

#endif