#include "server.h"
#include <thread>
#include <chrono>

int main(int argc, char* argv[]) {
    const auto port = static_cast<unsigned>(std::stoi(argv[1]));
    Server server{ port };
    server.run();
    while(true);
}