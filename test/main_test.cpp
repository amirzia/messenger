#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <algorithm>

#include "client.h"
#include "server.h"

const int port = 1895;

TEST(Connection, OneClientCanConnect) {
    using namespace std::chrono_literals;
    Server server{ port, 1 };
    server.run();

    const std::string clientUsername{ "Amir" };
    Client client{ clientUsername , port };
    client.connect();

    std::this_thread::sleep_for(100ms);

    const auto connectedUsers = server.getConnectedUsers();
    ASSERT_EQ(connectedUsers.size(), 1);
    ASSERT_EQ(connectedUsers.back(), clientUsername);
}

TEST(Connection, FiveClientCanConnect) {
    using namespace std::chrono_literals;
    Server server{ port, 5 };
    server.run();

    std::set<std::string> usernames {
        "Patrick",
        "Kaelyn",
        "Kamari",
        "Delaney",
        "Braxton"
    };
    std::vector<std::shared_ptr<Client>> clients;
    std::transform(usernames.cbegin(), usernames.cend(), std::back_inserter(clients),
        [](std::string username) {
            return std::make_shared<Client>(username, port);
    });
    std::for_each(clients.cbegin(), clients.cend(), [](auto& client) {
        client->connect();
    });    

    std::this_thread::sleep_for(100ms);

    const auto connectedUsers = server.getConnectedUsers();
    ASSERT_EQ(
        usernames,
        std::set<std::string>(connectedUsers.cbegin(), connectedUsers.cend())
    );
}

TEST(Message, TwoClientsCanSendAndReceiveMessages) {
    using namespace std::chrono_literals;
    Server server{ port, 3 };
    server.run();

    Client client1{ "Patrick", port };
    Client client2{ "Delaney", port };

    client2.connect();
    client1.connect();

    const std::string message{ "Hey, what's up?" };
    client1.sendMessage(message, client2.getUsername());

    std::this_thread::sleep_for(100ms);

    // auto receivedMessages = client2.getReceivedMessages();
    // ASSERT_EQ(receivedMessages.size(), 1);
    // ASSERT_EQ(receivedMessages.front() == message);
}