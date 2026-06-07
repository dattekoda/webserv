#ifndef MANAGER_HPP
# define MANAGER_HPP

# include "Socket.hpp"
# include <sys/epoll.h>

class	Server {
	int		_epollFD;
	SocketFD	_socketFD;

	epoll_event	*_ev_arr;
public:
	Server(const SocketFD &sfd);
	~Server();
};

#endif
