#ifndef EPOLLFD_HPP
#define EPOLLFD_HPP

#include <stdexcept>
#include <sys/epoll.h>
#include <unistd.h>

class EpollFd {
private:
  int fd_;

  EpollFd(const EpollFd &others);
  EpollFd &operator=(const EpollFd &others);

public:
  EpollFd() : fd_(-1) {
    if ((fd_ = ::epoll_create(0)) < 0) {
      throw std::runtime_error("epoll_create() failed");
    }
  }
  ~EpollFd() {
    if (fd_ != -1)
      ::close(fd_);
  }

  void add(int sfd);
  void del(int sfd);
  int wait(epoll_event *ev);
};

#endif
