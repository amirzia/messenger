#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <future>
#include <boost/asio.hpp>
#include "header.h"

using boost::asio::ip::tcp;
using std::string;

struct Client {
    Client(const string username, const int port);
    ~Client();
    void connect();
    const std::string getUsername();
    void sendMessage(std::string message, std::string to);
private:
	template <typename T>
	void sendObject(T object);
    static void printPrivateMessage(PrivateMessage& pm);

    boost::asio::io_context ic;
    tcp::socket socket;
    PrivateMessage incomingPm;
    const string username;
    std::future<void> readThread;
    const int port;
};

#endif