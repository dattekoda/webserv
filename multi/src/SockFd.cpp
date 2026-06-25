#include "SockFd.hpp"

void SockFd::setOptimumSock(addrinfo const *res) {
  addrinfo const *cur;
  int optval = 1;

  for (cur = res; cur; cur = cur->ai_next) {
    if ((fd_ = ::socket(cur->ai_family, cur->ai_socktype, cur->ai_protocol)) <
        0)
      continue;
    if (::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) <
        0) {
      ::close(fd_);
      continue;
    }
    if (::bind(fd_, cur->ai_addr, cur->ai_addrlen) == 0)
      break;
    ::close(fd_);
    fd_ = -1;
  }
  if (!cur)
    throw std::runtime_error("any candidates failed to bind()");
}
