#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include "client.h"

using namespace std::string_literals;

Client::Client(string username, const int port) : username{ username }, socket{ ic }, port{ port } {}
void Client::connect() {
    socket.connect(tcp::endpoint(
        boost::asio::ip::make_address_v4("127.0.0.1"),
        port
    ));
    boost::system::error_code ec;
	Header registerHeader{ UserRegisterT, username };
    sendObject(registerHeader);

    // thread to listen to messages from server
    readThread = std::async(std::launch::async, [self=this]() {
        while (true) {
            PrivateMessage pm;
            boost::system::error_code ec;
            boost::asio::mutable_buffer buf(&pm, sizeof(PrivateMessage));
            boost::asio::read(self->socket, buf, boost::asio::transfer_exactly(sizeof(PrivateMessage)), ec);
            if (ec) return;
            Client::printPrivateMessage(pm);
        }
    });
}

Client::~Client() {
    socket.close();
    ic.stop();
}

const std::string Client::getUsername() {
    return username;
}

void Client::sendMessage(std::string message, std::string to) {
	Header header{ PrivateMessageT, username, sizeof(PrivateMessage) };
    PrivateMessage pm{ username, to, message };
	sendObject<Header>(header);
    sendObject<PrivateMessage>(pm);
}

template <typename T>
void Client::sendObject(T object) {
	boost::system::error_code ec;
	boost::asio::write(socket, boost::asio::buffer(&object, sizeof(T)), ec);
}

void Client::printPrivateMessage(PrivateMessage& pm) {
    std::cout   << "[" << pm.getSender() << "] "
                << pm.getMessage() << std::endl;
}