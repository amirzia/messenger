
#include <string>
#include "user.h"

User::User(string username) :
    username{ std::move(username) } {}

auto User::getUsername() -> string {
    return username;
}