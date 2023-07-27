#include "tcpstream.h"

TCP_Stream::TCP_Stream(int asock, struct sockaddr_in *info) :
	sock(asock) 
{
	char temp_address[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, (struct sockaddr *) info, temp_address, INET_ADDRSTRLEN);
	peer_port = ntohs(info->sin_port);
	peer_add = temp_address;
}

void TCP_Stream::send_message(Message amessage)
{
	char message[MAX_SIZE];

	memset(message, 0, sizeof(message));
	sprintf(message, "%02d%s", (int) amessage.get_size(), amessage.get_message_tosend());
	std::cout << "sending" << message << std::endl;
	sendto(message, strlen(message));
}

void TCP_Stream::read_message()
{
	char temp[MAX_SIZE];
	int size;
	int retval = 0;

	memset(temp, 0, sizeof(temp));
	retval = receive(temp, 2);
	if (retval == 2)
	{
		memset(temp, 0, sizeof(temp));
		receive(temp, size);
		Message message(temp);
		messages.push_back(message);
	}
}

int TCP_Stream::get_sock()
{
	return (sock);
}

size_t TCP_Stream::sendto(const char *buffer, size_t len)
{
	size_t retval;
	retval = send(sock, buffer, len, 0);
	return (retval);
}

size_t TCP_Stream::receive(char *buffer, size_t len)
{
	size_t retval;
	retval = read(sock, buffer, len);
	return (retval);
}

void TCP_Stream::cleanup()
{
	close(sock);
}

std::string TCP_Stream::get_addr()
{
	return (peer_add);
}

int TCP_Stream::get_port()
{
	return (peer_port);
}
