#include "Server.hpp"
#include "Fdlib.hpp"
#include "Config.hpp"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <stdexcept>
#include <new>
#include <unistd.h>

Server::Server(const Config *conf) :
	epollFD_(-1),
	ev_arr_(0),
	count_(0),
	nfds_(-1),
	conf_(conf) {
	try {
		Server::setSockets(conf_->servers_);
		epollFD_ = ::epoll_create(1);
		if (epollFD_ < 0)
			throw std::runtime_error("epoll_create failed");
		Server::addSockets();
		ev_arr_ = new epoll_event[MAX_CHILD];
	} catch (const std::exception& e) {
		if (epollFD_ != -1)
			::close(epollFD_);
		for (size_t i = 0; i < socketFDs_.size(); ++i)
			delete socketFDs_[i];
		socketFDs_.clear();
		delete[] ev_arr_;
		throw ;
	}
}

Server::~Server() {
	if (epollFD_ != -1)
		close(epollFD_);
	delete[] ev_arr_;
	for (size_t i = 0; i < socketFDs_.size(); ++i)
		delete socketFDs_[i];
	socketFDs_.clear();
}

void	Server::setSockets(const std::vector<ServerConfig> &servers) {
	socketFDs_.reserve(servers.size());
	for (size_t i = 0; i < servers.size(); ++i) {
		SocketFD*	sfdPtr = new SocketFD(servers[i].host_.port_);
		socketFDs_.push_back(sfdPtr);
	}
}

void	Server::addSockets(void) {
	struct epoll_event	ev;

	for (size_t i = 0; i < socketFDs_.size(); ++i) {
		ev.data.fd = socketFDs_[i]->getFD();
		ev.events = EPOLLIN;
		if (::epoll_ctl(epollFD_, EPOLL_CTL_ADD, socketFDs_[i]->getFD(), &ev) < 0)
			throw std::runtime_error("epoll_ctl() failed");
	}
}

// void	Server::run(void) {
// 	while (true) {
// 		std::cerr << "<<child count " << count_ << ">>" << std::endl;
// 		switch((nfds_ = epoll_wait(epollFD_, ev_arr_, MAX_CHILD+1, -1))) {
// 			case -1:
// 				throw std::runtime_error("epoll_wait() failed");
// 			case 0:
// 				break ;
// 			default:
// 				handleActions();
// 				break ;
// 		}
// 	}
// }
//
// void	Server::handleActions(void) {
// 	for (int i = 0; i < nfds_; ++i) {
// 		if (ev_arr_[i].data.fd == socketFD_.getFD()) {
// 			Server::addFD();
// 			continue ;
// 		}
// 		Server::processEvents(i);
// 	}
// }
//
// // new connection has arrived!
// void	Server::addFD(void) {
// 	int			arrivedFD;
// 	struct sockaddr_storage	from;
// 	socklen_t		len = (socklen_t)sizeof(from);
//
// 	if ((arrivedFD = ::accept(socketFD_.getFD(), (struct sockaddr *)&from, &len)) < 0) {
// 		if (errno == EAGAIN || errno == EWOULDBLOCK)
// 			return ;
// 		if (errno != EINTR)
// 			throw std::runtime_error("accept() failed");
// 		return ;
// 	}
// 	// htons(((struct sockaddr_in *)&from)->sin_port);
// 	if (MAX_CHILD <= count_+1) {
// 		::close(arrivedFD);
// 		std::cerr << "connection is full: cannot accept\n";
// 		return ;
// 	}
// 	if (Fdlib::setNonblock(arrivedFD) < 0)
// 		::close(arrivedFD);
// 		throw std::runtime_error("fcntl() failed");
// 	}
// 	epoll_event		ev;
// 	ev.data.fd = arrivedFD;
// 	ev.events = EPOLLIN;
// 	if (epoll_ctl(epollFD_, EPOLL_CTL_ADD, arrivedFD, &ev) < 0) {
// 		::close(arrivedFD);
// 		throw std::runtime_error("epoll_ctl() failed");
// 	}
// 	++count_;
// }
//
// void	Server::processEvents(int i) {
// 	if (handleIO(i) < 0) {
// 		if (::epoll_ctl(epollFD_, EPOLL_CTL_DEL, ev_arr_[i].data.fd, NULL) < 0) {
// 			::close(ev_arr_[i].data.fd);
// 			::close(epollFD_);
// 			throw std::runtime_error("epoll_ctl() failed");
// 		}
// 		::close(ev_arr_[i].data.fd);
// 		--count_;
// 	}
// }
//
// size_t	ft_strlcat(char *dst, const char *src, size_t size);
//
// int	Server::handleIO(int i) {
// 	char	buf[512], *ptr;
// 	ssize_t	len;
//
// 	if ((len = ::recv(ev_arr_[i].data.fd, buf, sizeof(buf)-1, 0)) == -1) {
// 		std::cerr << "recv() failed" << std::endl;
// 		return -1;
// 	}
// 	if (len == 0) {
// 		std::cerr << "[child" << i << "]recv:EOF" << std::endl;
// 		return -1;
// 	}
// 	buf[len] = '\0';
// 	if ((ptr = ::strpbrk(buf, "\r\n")) != NULL) {
// 		*ptr = '\0';
// 	}
// 	std::cerr << "[child" << i << "]" << buf << std::endl;
// 	ft_strlcat(buf, ":OK\r\n", sizeof(buf));
// 	len = ::strlen(buf);
// 	if ((len = ::send(ev_arr_[i].data.fd, buf, len, 0)) == -1) {
// 		std::cerr << "send() failed" << std::endl;
// 		return -1;
// 	}
// 	return 0;
// }
//
// size_t	ft_strlcat(char *dst, const char *src, size_t size) {
// 	const size_t	dst_len = ::strnlen(dst, size);
// 	const size_t	src_len = ::strlen(src);
//
// 	dst += dst_len;
// 	size -= dst_len;
// 	while (1 < size && *src)
// 		*(dst++) = (--size, *(src++));
// 	if (size)
// 		*dst = '\0';
// 	return (dst_len + src_len);
// }
//
