#include "client.h"

void printHelp() {
    std::cout   << "Send message in this format:" << std::endl
                << "<receiver> <message>" << std::endl;
}

int main(int argc, char* argv[]) {
    const int port = std::stoi(argv[1]);
    std::string username = argv[2];
    Client client{ username, port };
    client.connect();

    printHelp();
    while (true) {
        std::string receiver, message;
        std::getline(std::cin, receiver, ' ');
        std::getline(std::cin, message);
        client.sendMessage(message, receiver);
    }
}