#include "Server.hpp"
#include <stdexcept>
#include <unistd.h>

Server::Server(const SocketFD &sfd) : _epollFD(-1), _socketFD(sfd) {
	_epollFD = ::epoll_create(0);
	if (_epollFD < 0)
		throw std::runtime_error("epoll_create failed");
	struct epoll_event	ev;

	ev.data.fd = _socketFD.getFD();
	ev.events = EPOLLIN;
	if (epoll_ctl(_epollFD, EPOLL_CTL_ADD, _socketFD.getFD(), &ev))
		throw std::runtime_error("epoll_ctl() failed");
}

Server::~Server() {
	if (_epollFD != -1)
		close(_epollFD);
}

