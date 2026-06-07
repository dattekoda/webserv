#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <string>

class	SocketFD {
private:
	int	_fd;
public:
	SocketFD(const std::string &portnum);
	~SocketFD();

	int	getFD(void) const ;
};

#endif
