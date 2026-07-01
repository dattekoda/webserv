#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <sys/socket.h>
#include <sys/types.h>

#define FIRSTIP  0xff
#define SECONDIP 0x00ff
#define THIRDIP  0x0000ff
#define FOURTHIP 0x000000ff
#define BUF_SIZE 4096

// std::ostream &operator<<(std::ostream &os, in_addr_t i) {
//   os << (int)(i & 0x000000ff) << ".";
//   os << (int)(i & 0x0000ff) << ".";
//   os << (int)(i & 0x00ff) << ".";
//   os << (int)(i & 0xff);
//   return os;
// }

void begin_server(int sfd) {
  int afd;
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  char buf[BUF_SIZE];

  while (true) {
    if ((afd = ::accept(sfd, (sockaddr *)&addr, &addr_len) < 0))
      throw std::runtime_error("accept() failed");
    std::cerr << addr.sin_addr.s_addr << std::endl;
    ssize_t recvret;
    if ((recvret = recv(afd, buf, BUF_SIZE, MSG_DONTWAIT)) < 0) {
      throw std::runtime_error("recv() failed");
    }
  }
}
