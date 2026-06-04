#include <string>

using namespace	std;

class SocketFD {
private:
	int	_fd;

	SocketFD(const SocketFD& others);
	SocketFD&	operator=(const SocketFD& others);
public:
	SocketFD(const string &port);	// socket(), bind(), listen()
	~SocketFD();			// close()

	int	getFD(void) const ;
};

