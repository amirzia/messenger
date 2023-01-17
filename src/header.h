#ifndef HEADER_H
#define HEADER_H

#include <array>
#include <string>

enum HeaderType : short {
	UserRegisterT,
	UserExitT,
	PrivateMessageT
};

struct Header {
	Header() = default;
	Header(HeaderType headerType_, std::string sender_, short bodySize = 0);
	std::string getSender() const;

	HeaderType type{}; // 1 byte. 1: userConnect, 2: userExits, 3: privateMessage
    std::array<char, 16> sender{}; // 16 bytes
    short bodySize{}; // 4 bytes
};

struct PrivateMessage {
	PrivateMessage() = default;
	PrivateMessage(std::string from_, std::string to_, std::string message_);
	std::string getReceiver() const;
	std::string getSender() const;
	std::string getMessage() const;

	std::array<char, 16> from{};
	std::array<char, 16> to{};
	std::array<char, 1024> message{};
};

#endif