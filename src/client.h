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
    Client(string username, const int port);
    void connect();
private:
    boost::asio::io_context ic;
    tcp::socket socket; 
    string username;
    const int port;
};

#endif