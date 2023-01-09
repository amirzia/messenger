#include <iostream>
#include <thread>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std::string_literals;
using ip::tcp;
using std::string;
using std::cout;
using std::cin;
using std::endl;

auto getUsername() -> string {
    string username;
    cout << "Enter username without space: ";
    cin >> username;
    return username;
}

// struct Client {

// }



int main() {
    auto username = getUsername();
    
    io_context ic;
    tcp::socket socket{ ic };
    socket.connect(tcp::endpoint(
        ip::address::from_string("127.0.0.1"),
        1895
    ));
    boost::system::error_code ec;
    const string message = "Hello from"s + username + '\n';
    boost::asio::write(socket, buffer(message), ec);
    if (ec) cout << "Error: " << ec.what() << endl;
}