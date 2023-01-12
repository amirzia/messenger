#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <algorithm>

#include "client.h"
#include "server.h"

const int port = 1895;

TEST(Server, OneClientCanConnect) {
    using namespace std::chrono_literals;
    Server server{ port };
    server.run();

    const std::string clientUsername{ "Amir" };
    Client client{ clientUsername , port };
    client.connect();

    std::this_thread::sleep_for(1s);

    const auto connectedUsers = server.getConnectedUsers();
    ASSERT_EQ(connectedUsers.size(), 1);
    ASSERT_EQ(connectedUsers.back(), clientUsername);
}

TEST(Server, FiveClientCanConnect) {
    using namespace std::chrono_literals;
    Server server{ 1895 };
    server.run();

    std::set<const std::string> usernames {
        "Patrick",
        "Kaelyn",
        "Kamari",
        "Delaney",
        "Braxton"
    };
    std::for_each(usernames.cbegin(), usernames.cend(), [](const auto& username) {
        Client client{ username, port };
        client.connect();
    });    

    std::this_thread::sleep_for(1s);

    const auto connectedUsers = server.getConnectedUsers();
    ASSERT_EQ(
        usernames,
        std::set<const std::string>(connectedUsers.cbegin(), connectedUsers.cend())
    );
}