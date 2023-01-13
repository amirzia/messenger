#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <boost/asio.hpp>

#ifndef CLIENT_H
#define CLIENT_H

using boost::asio::ip::tcp;
using std::string;

struct Client {
    Client(const string username, const int port);
    void connect();
    const std::string getUsername();
    void sendMessage(std::string message, std::string to);
private:
    boost::asio::io_context ic;
    tcp::socket socket; 
    const string username;
    const int port;
};

#endif