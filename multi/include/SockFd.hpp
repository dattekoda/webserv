#ifndef SOCKFD_HPP
#define SOCKFD_HPP

#include "AddrInfo.hpp"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class SockFd {
private:
  int fd_;

  void setOptimumSock(const addrinfo *res);

  SockFd(const SockFd &others);
  SockFd &operator=(const SockFd &others);

public:
  SockFd(const char *host, const char *service, int backlog) : fd_(-1) {
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
    hints.ai_protocol = IPPROTO_TCP;

    AddrInfo info(host, service, &hints);
    setOptimumSock(info.get());
    if (::listen(fd_, backlog) < 0) {
      ::close(fd_);
      throw std::runtime_error("listen() failed");
    }
  }
  ~SockFd() {
    if (fd_ != -1)
      ::close(fd_);
    fd_ = -1;
  }
  int get(void) const { return fd_; }
};

#endif
