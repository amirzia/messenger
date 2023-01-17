
#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <future>
#include <boost/asio.hpp>

#include "header.h"

#define DEFAULT_SERVER_THREADS 4

using boost::asio::ip::tcp;

struct Server {
    Server(const unsigned port, const int n_threads = DEFAULT_SERVER_THREADS);
    ~Server();
    void run();
    void stop();
    std::vector<std::string> getConnectedUsers();
    void serve(boost::asio::ip::tcp::acceptor& acceptor);
    void receive(std::string username);
    void sendMessage(std::string message, std::string from, std::string to);

private:
	template <typename T>
	T readFromSocket(std::shared_ptr<tcp::socket> socket);
    template<typename T>
    void sendObject(T object, std::shared_ptr<boost::asio::ip::tcp::socket> socket_ptr);
    static void printPrivateMessage(PrivateMessage& pm);

    const int n_threads;
    boost::asio::io_context ic;
    boost::asio::ip::tcp::acceptor acceptor;
    std::unordered_map<std::string, std::shared_ptr<boost::asio::ip::tcp::socket>> userToSocket;
    std::vector<std::future<void>> ic_threads;
    std::future<void> readHandler;
};

#endif