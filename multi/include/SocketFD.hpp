#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <string>

class	SocketFD {
private:
	int	fd_;

	void	setOptimalSocket(const struct addrinfo *res);

	SocketFD(const SocketFD& others);
	SocketFD&	operator=(const SocketFD& others);
public:
	SocketFD(const std::string &portnum);
	~SocketFD();

	int	getFD(void) const ;
};

#endif
