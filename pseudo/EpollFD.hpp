#include "Socket.hpp"
#include <sys/epoll.h>

class EpollFD {
private:
	int	_fd;

	EpollFD(const EpollFD& others);
	EpollFD&	operator=(const EpollFD& others);
public:
	EpollFD();
	~EpollFD();

	void	add(const SocketFD &socket_fd, struct epoll_event *ev);
	int	wait(struct epoll_event *ev, int timeout);
};

