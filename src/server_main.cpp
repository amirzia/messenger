#include "server.h"
#include <thread>
#include <chrono>

int main() {
    Server server{ 1895 };
    server.run();

    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5s);

    std::cout << "Conn users: " << server.getConnectedUsers().size();
}