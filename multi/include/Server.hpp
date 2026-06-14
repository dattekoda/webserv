#ifndef SERVER_HPP
# define SERVER_HPP

# include "SocketFD.hpp"
# include "Config.hpp"
# include "Connection.hpp"
# include <sys/epoll.h>
# include <vector>

# ifndef MAX_CHILD
#  define MAX_CHILD 32
# endif

class IEpollModifier {
public:
	virtual	~IEpollModifier() {}

	virtual void	handleEvent(int fd, uint32_t events) = 0;
	// virtual int	epollAdd(int fd, uint32_t event) = 0;
	// virtual int	epollMod(int fd, uint32_t event) = 0;
	// virtual int	epollDel(int fd) = 0;
};

class	Server : public IEpollModifier {
	int		epollFD_;
	epoll_event	*ev_arr_;
	int		count_;
	int		nfds_;
	const Config	*conf_;

	std::vector<SocketFD*>		socketFDs_;
	std::map<int, Connection*>	connections_;

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
	int	epollAdd(int fd, uint32_t event);
	int	epollMod(int fd, uint32_t event);
	int	epollDel(int fd);
};

#endif
