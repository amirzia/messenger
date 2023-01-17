#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <future>
#include <boost/asio.hpp>

#include "server.h"

Server::Server(const unsigned port, const int n_threads) :
    acceptor{ ic, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port) },
    n_threads{ n_threads },
    ic{ n_threads } {
    serve(acceptor);
}

void Server::run() {
    std::generate_n(std::back_inserter(ic_threads), n_threads,
        [self=this]() {
            return std::async(std::launch::async, [self] { self->ic.run(); });
    });
}

void Server::stop() {
    ic.stop();
}

Server::~Server() {
    stop();
}

std::vector<std::string> Server::getConnectedUsers() {
    std::vector<std::string> connectedUsers{}; 
    for (const auto& it : userToSocket) {
        connectedUsers.push_back(it.first);
    }
    return connectedUsers;
}

void Server::serve(boost::asio::ip::tcp::acceptor& acceptor) {
    try {
        acceptor.async_accept([self=this, &acceptor](boost::system::error_code ec, boost::asio::ip::tcp::socket socket) {
            self->serve(acceptor);
            if (ec) {
                std::cout << "Error in accepting new connections: " << ec.value() << std::endl;
                return;
            }
            auto socket_ptr = std::make_shared<tcp::socket>(std::move(socket));
            Header header = self->readFromSocket<Header>(socket_ptr);
			std::string username = header.getSender();
            std::cout << "User: " << username << " joined" << std::endl;
            self->userToSocket.insert({ username, socket_ptr });
            self->receive(username);
        });
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

template <typename T>
T Server::readFromSocket(std::shared_ptr<tcp::socket> socket) {
	T object{};
	boost::asio::mutable_buffer buf(&object, sizeof(T));
    boost::system::error_code ec;
	boost::asio::read(*socket, buf, boost::asio::transfer_exactly(sizeof(T)), ec);
    if (ec) return {};
    return object;
}

void Server::receive(std::string username) {
    auto socket = userToSocket.at(username);
    Header header = readFromSocket<Header>(socket);
    switch (header.type) {
        case PrivateMessageT:
            PrivateMessage pm = readFromSocket<PrivateMessage>(socket);
            Server::printPrivateMessage(pm);
            sendMessage(pm.getMessage(), pm.getSender(), pm.getReceiver());
            break;
    }
}

void Server::sendMessage(std::string message, std::string from, std::string to) {
    PrivateMessage pm{ from, to, message };
    auto socket_ptr = userToSocket.at(to);
    sendObject<PrivateMessage>(pm, socket_ptr);
}

template <typename T>
void Server::sendObject(T object, std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr) {
    boost::system::error_code ec;
	boost::asio::write(*socket_ptr, boost::asio::buffer(&object, sizeof(T)), ec);
}

void Server::printPrivateMessage(PrivateMessage& pm) {
    std::cout   << "[" << pm.getSender() << "]"
                << " -> "
                << "[" << pm.getReceiver() << "] "
                << pm.getMessage() << std::endl;
}