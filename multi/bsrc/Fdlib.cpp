#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>

namespace	Fdlib {
	int	setNonblock(int fd) {
		int	flags = ::fcntl(fd, F_GETFL, 0);
		if (flags < 0 || fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
			return -1;
		return 0;
	}
}

