#include "Socket.hpp"
#include <stdexcept>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

SocketFD::SocketFD(const std::string &portnum) : _fd(-1) {
	struct addrinfo	hints, *res;
	int		errcode;

	::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		// using ipv4
	hints.ai_socktype = SOCK_STREAM;	// using tcp
	hints.ai_flags = AI_PASSIVE;		// mean you can receive all of ip addresses.
	errcode = ::getaddrinfo(NULL, portnum.c_str(), &hints, &res);
	// get suitable address undirectional list based on 2 inputs, portnum and hints
	if (errcode != 0)
		throw std::runtime_error(gai_strerror(errcode));
	_fd = ::socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (_fd < 0) {
		::freeaddrinfo(res);
		throw std::runtime_error("socket() failed");
	}
	int	opt = 1;
	// set for avoiding 'Address already in use'
	if (::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
		::freeaddrinfo(res);
		throw std::runtime_error("setsockopt() failed");
	}
	if (::bind(_fd, res->ai_addr, res->ai_addrlen) < 0) {
		::freeaddrinfo(res);
		throw std::runtime_error("bind() failed");
	}
	// SOMAXCONN: 128 which represents the limited value on linux
	if (listen(_fd, SOMAXCONN) < 0) {
		::freeaddrinfo(res);
		throw std::runtime_error("listen() failed");
	}
	freeaddrinfo(res);
}

SocketFD::~SocketFD() {
	if (_fd != -1)
		close(_fd);
}

int	SocketFD::getFD(void) const {
	return _fd;
}

