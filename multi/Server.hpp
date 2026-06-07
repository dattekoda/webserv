#ifndef MANAGER_HPP
# define MANAGER_HPP

# include "SocketFD.hpp"
# include <sys/epoll.h>

# ifndef MAX_CHILD
#  define MAX_CHILD 32
# endif

class	Server {
	int		epollFD_;
	SocketFD	socketFD_;

	epoll_event	*ev_arr_;

	int		count_;
	int		nfds_;

	void		handleActions(void);

	void		accept(void);
	void		processEvents(int i);

	int		handleIO(int i);

	Server(const Server& others);
	Server&	operator=(const Server &others);
public:
	Server(const SocketFD &sfd);
	~Server();

	void	run(void);
};

#endif
