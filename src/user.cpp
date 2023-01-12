
#include <string>
#include "user.h"

User::User(string username) :
    username{ std::move(username) } {}

auto User::getUsername() const -> string {
    return username;
}