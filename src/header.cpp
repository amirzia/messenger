#include "header.h"

Header::Header(HeaderType headerType_, std::string sender_, short bodySize) : 
	type{ headerType_ }, bodySize{ bodySize } {
	std::copy_n(sender_.begin(), sender_.size(), sender.begin());
}

std::string Header::getSender() const {
	return { sender.data() };
}

PrivateMessage::PrivateMessage(std::string from_, std::string to_, std::string message_) {
	std::copy_n(from_.begin(), from_.size(), from.begin());
	std::copy_n(to_.begin(), to_.size(), to.begin());
	std::copy_n(message_.begin(), message_.size(), message.begin());	
}

std::string PrivateMessage::getMessage() const {
	return { message.data() };
}

std::string PrivateMessage::getReceiver() const {
	return { to.data() };
}

std::string PrivateMessage::getSender() const {
	return { from.data() };
}