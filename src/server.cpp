#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace std::string_literals;
using ip::tcp;
using std::string;
using std::cout;
using std::endl;

struct Session : std::enable_shared_from_this<Session> {
    explicit Session(ip::tcp::socket socket) : socket{ std::move(socket) } {}
    void read() {
        async_read_until(socket, dynamic_buffer(message), '\n',
            [self=shared_from_this()] (boost::system::error_code ec,
                                       std::size_t length) {
                if (ec) {
                    cout << "Error in connecting: " << ec.value() << endl;
                    return;
                }
                // do something on message
                self->message = "Got it: "s + self->message;
                cout << self->message << endl;
                self->responde();
            }
        );
    }
    void responde() {
        async_write(socket, buffer(message),
            [self=shared_from_this()] (boost::system::error_code ec,
                                       std::size_t length) {
                if (ec) return;
                self->message.clear();
                self->read();
                });
    }
    private:
    tcp::socket socket;
    string message;
};

void serve(ip::tcp::acceptor& acceptor) {
    acceptor.async_accept([&acceptor](boost::system::error_code ec, ip::tcp::socket socket) {
        serve(acceptor);
        if (ec) {
            cout << "Error in accepting new connections: " << ec.value() << endl;
            return;
        }
        auto session = std::make_shared<Session>(std::move(socket));
        session->read();
    });
}

int main() {
    try {
        io_context ic;
        tcp::acceptor acceptor{ ic, tcp::endpoint(tcp::v4(), 1895) };
        serve(acceptor);
        ic.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}