#include "client.h"

int main(int argc, char* argv[]) {
    Client client{ std::string{ argv[1] }, 1895 };
    client.connect();
}