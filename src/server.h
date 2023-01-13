
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <future>
#include <boost/asio.hpp>

#define DEFAULT_SERVER_THREADS 4

struct Server {
    Server(const unsigned port, const int n_threads = DEFAULT_SERVER_THREADS);
    ~Server();
    void run();
    void stop();
    std::vector<std::string> getConnectedUsers();
    void serve(boost::asio::ip::tcp::acceptor& acceptor);
    void receive(std::string username);

private:
    const int n_threads;
    boost::asio::io_context ic;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map<std::string, boost::asio::ip::tcp::socket> userToSocket;
    std::vector<std::future<void>> ic_threads;
};

#endif