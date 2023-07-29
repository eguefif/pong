#pragma once
#include "def.h"
#include "message.h"

class TCP_Stream
{
public:
	TCP_Stream() = default;
	TCP_Stream(int asock, struct sockaddr_in *info);
	void send_message(Message message);
	void read_message();
	void cleanup();
	int get_sock();
	std::string get_addr();
	int get_port();

	std::vector<Message> messages;

private:
	int sock;
	std::string peer_add;
	int peer_port;

	size_t sendto(const char *buffer, size_t len);
	size_t receive(char *buffer, size_t len);
	void add_protoheader(char *message, Message amessage);
};
