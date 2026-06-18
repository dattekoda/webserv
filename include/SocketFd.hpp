#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>

class SocketFd {
private:
	int	fd_;
public:
	SocketFd(const std::string &portno);
	//socket(), bind(), listen()
};

#endif

