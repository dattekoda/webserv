#include <sys/epoll.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#include <ctype.h>
#include <errno.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>
#include <unistd.h>

#define	MAX_CHILD	32

int	send_recv(int acc, int child_no);

void	accept_loop(int soc) {
	char	hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
	struct sockaddr_storage	from;
	int	acc, count, epollfd, nfds, ret;
	socklen_t	len;
	struct epoll_event	ev, events[MAX_CHILD];

	if ((epollfd = epoll_create(MAX_CHILD + 1)) == -1) {
		perror("epoll_create");
		return ;
	}
	ev.data.fd = soc;
	ev.events = EPOLLIN;
	if (epoll_ctl(epollfd, EPOLL_CTL_ADD, soc, &ev) == -1) {
		perror("epoll_ctl");
		(void) close(epollfd);
		return ;
	}
	count = 0;
	while (1) {
		(void) fprintf(stderr, "<<child count:%d>>\n", count);
		switch ((nfds = epoll_wait(epollfd, events, MAX_CHILD+1, 10 * 1000))) {
			case -1:
				perror("epoll_wait");
				break ;
			case 0:
				break ;
			default:
				for (int i = 0; i < nfds; i++) {
					// every set event is ready.
					if (events[i].data.fd == soc) {
						// new connection has come!
						len = (socklen_t)sizeof(from);
						if ((acc=accept(soc, (struct sockaddr*)&from, &len)) == -1) {
							if (errno != EINTR)
								perror("accept");
						} else {
							(void) getnameinfo((struct sockaddr*)&from, len,
									hbuf, sizeof(hbuf),
									sbuf, sizeof(sbuf),
									NI_NUMERICHOST | NI_NUMERICSERV);
							(void) fprintf(stderr, "accept:%s:%s\n", hbuf, sbuf);
							if (count+1 >= MAX_CHILD) {
								(void) fprintf(stderr, "connection is ful: cannot accept\n");
								(void) close(acc);
								continue ;
							}
							// set new fd
							ev.data.fd = acc;
							ev.events = EPOLLIN;
							if (epoll_ctl(epollfd, EPOLL_CTL_ADD, acc, &ev) == -1) {
								perror("epoll_ctl");
								(void) close(acc);
								(void) close(epollfd);
								return ;
							}
							++count;
						}
						continue ;
					}
					if ((ret = send_recv(events[i].data.fd, events[i].data.fd)) == -1) {
						if (epoll_ctl(epollfd,
								EPOLL_CTL_DEL,
								events[i].data.fd,
								&ev) == -1) {
							perror("epoll_ctl");
							(void) close(events[i].data.fd);
							(void) close(epollfd);
							return ;
						}
						(void) close(events[i].data.fd);
						--count;
					}
				}
				break ;
		}
	}
	(void) close(epollfd);
}

