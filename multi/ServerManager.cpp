#include "Server.hpp"
#include <stdexcept>

Server::Server(const SocketFD &sfd) {
	_epollFD = ::epoll_create(0);
	if (_epollFD < 0)
		throw std::runtime_error("epoll_create failed");
}

