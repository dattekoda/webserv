#include "SocketFD.hpp"
#include "Fdlib.hpp"
#include <fcntl.h>
#include <stdexcept>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

SocketFD::SocketFD(const std::string &portnum) : fd_(-1) {
	struct addrinfo	hints, *res;
	int		errcode;

	::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;		// using ipv4
	hints.ai_socktype = SOCK_STREAM;	// using tcp
	hints.ai_flags = AI_PASSIVE;		// mean you can receive all of ip addresses.
	errcode = ::getaddrinfo(NULL, portnum.c_str(), &hints, &res);
	// get suitable address undirectional list based on 2 inputs, portnum and hints
	if (errcode != 0)
		throw std::runtime_error(gai_strerror(errcode));
	try {
		setOptimalSocket(res);
	} catch (const std::runtime_error &e) {
		if (fd_ != -1)
			::close(fd_);
		freeaddrinfo(res);
		throw ;
	}
	freeaddrinfo(res);
	if (listen(fd_, SOMAXCONN) < 0) {
		::close(fd_);
		throw std::runtime_error("listen() failed");
	}
	if (Fdlib::setNonblock(fd_) < 0) {
		::close(fd_);
		throw std::runtime_error("fcntl() failed");
	}
}

void	SocketFD::setOptimalSocket(const struct addrinfo *res) {
	int	opt = 1;

	for (const struct addrinfo *rp = res; rp; rp = rp->ai_next) {
		fd_ = ::socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (fd_ < 0)
			throw std::runtime_error("socket() failed");
		// set for avoiding 'Address already in use'
		if (::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
			::close(fd_);
			throw std::runtime_error("setsockopt() failed");
		}
		if (::bind(fd_, rp->ai_addr, rp->ai_addrlen) == 0)
			break ;
		::close(fd_);
		fd_ = -1;
	}
	if (fd_ == -1)
		throw std::runtime_error("could not bind to any address");
}

SocketFD::~SocketFD() {
	if (fd_ != -1)
		::close(fd_);
}

int	SocketFD::getFD(void) const {
	return fd_;
}

