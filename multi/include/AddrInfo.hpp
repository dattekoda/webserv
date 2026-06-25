#ifndef ADDRINFO_HPP
#define ADDRINFO_HPP

#include <netdb.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>

class AddrInfo {
private:
  addrinfo *res_;
  AddrInfo(const AddrInfo &others);
  AddrInfo &operator=(const AddrInfo);

public:
  AddrInfo(const char *host, const char *service, const addrinfo *hints)
      : res_(0) {
    if (getaddrinfo(host, service, hints, &res_) != 0) {
      throw std::runtime_error("getaddrinfo() failed");
    }
  }
  ~AddrInfo() {
    if (res_)
      freeaddrinfo(res_);
  }
  addrinfo *get() const { return res_; }
};

#endif
