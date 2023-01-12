
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <future>
#include <boost/asio.hpp>

struct Server {
    Server(const unsigned port);
    ~Server();
    void run();
    void stop();
    std::vector<std::string> getConnectedUsers();
    void serve(boost::asio::ip::tcp::acceptor& acceptor);

private:
    boost::asio::io_context ic;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map<std::string, boost::asio::ip::tcp::socket> userToSocket;
    std::future<void> ic_thread;
};

#endif