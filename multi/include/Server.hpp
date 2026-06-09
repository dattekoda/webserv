#ifndef MANAGER_HPP
# define MANAGER_HPP

# include "SocketFD.hpp"
# include "Config.hpp"
# include <sys/epoll.h>
# include <vector>

# ifndef MAX_CHILD
#  define MAX_CHILD 32
# endif

class	Server {
	int		epollFD_;
	epoll_event	*ev_arr_;
	int		count_;
	int		nfds_;
	const Config	*conf_;
	std::vector<SocketFD*>	socketFDs_;

	void		handleActions(void);

	void		accept(int fd);
	void		processEvents(int i);

	bool		isMonitoringFDs(int fd);
	int		handleIO(int i);

	void		setSockets(const std::vector<ServerConfig> &servers);
	void		addSockets(void);

	Server(const Server& others);
	Server&	operator=(const Server &others);
public:
	Server(const Config *conf);
	~Server();

	void	run(void);
};

#endif
