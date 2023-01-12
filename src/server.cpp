#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <future>
#include <boost/asio.hpp>
#include "server.h"

Server::Server(const unsigned port) :
    acceptor{ ic, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port) } {
    serve(acceptor);
}

void Server::run() {
    ic_thread = std::async(std::launch::async, [this]() {
        ic.run();
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

            boost::system::error_code error_code;
            std::string username{};
            boost::asio::read_until(socket, boost::asio::dynamic_buffer(username), "\0", error_code);
            if (error_code)
                throw std::runtime_error{ "Error in getting register message from client" };
            
            self->userToSocket.insert({ username, std::move(socket) });
        });
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}