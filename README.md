# Messanger

An asynchronous, multithreaded chat server using Boost.Asio.

## Build and run

To build the server, client, and test binaries issue:
```
cmake -S . -B build
cmake --build build
```

First, run the server on localhost:
```
./build/src/server <port>
```

Then, run the clients:
```
./build/src/client <port> <username>
```

## Test
```
./build/test/main_test
```
