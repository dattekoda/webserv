#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define LISTEN_SIZE 30
#define EVENT_SIZE 20

int main(int argc, char *argv[]) {
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);
  memset(&addr, 0, addr_len);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  addr.sin_addr.s_addr = 0x0100007F;
  if (bind(sockfd, (struct sockaddr *)(&addr), addr_len) < 0) {
    close(sockfd);
    return 1;
  }
  if (listen(sockfd, LISTEN_SIZE) < 0) {
    close(sockfd);
    return 1;
  }
  int fd = epoll_create(0);
  struct epoll_event ev[EVENT_SIZE];

  while (true) {
    if (int nfds = epoll_wait(fd, ev, EVENT_SIZE, -1) == -1) {
      return 1;
    }
  }
  close(fd);
  return 0;
}
