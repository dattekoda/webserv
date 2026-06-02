#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include <unistd.h>

#include <stdio.h>
#include <string.h>

int	server_socket(const char *portnm) {
	char	nbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
	struct addrinfo	hints, *res0;
	int	soc, opt, errcode;
	socklen_t	opt_len;

	(void) memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((errcode = getaddrinfo(NULL, portnm, &hints, &res0)) != 0) {
		(void) fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(errcode));
		return -1;
	}
	if ((errcode = getnameinfo(res0->ai_addr, res0->ai_addrlen,
				nbuf, sizeof(nbuf),
				sbuf, sizeof(sbuf),
				NI_NUMERICHOST|NI_NUMERICSERV)) != 0) {
		(void) fprintf(stderr, "getnameinfo(): %s\n", gai_strerror(errcode));
		freeaddrinfo(res0);
		return -1;
	}
	fprintf(stderr, "port=%s\n", sbuf);
	if ((soc = socket(res0->ai_family, res0->ai_socktype, res0->ai_protocol)) == -1) {
		perror("socket");
		freeaddrinfo(res0);
		return -1;
	}
	opt = 1;
	opt_len = sizeof(opt);
	if (setsockopt(soc, SOL_SOCKET, SO_REUSEADDR, &opt, opt_len)==-1) {
		perror("setsockopt");
		(void) close(soc);
		freeaddrinfo(res0);
		return -1;
	}
	if (bind(soc, res0->ai_addr, res0->ai_addrlen) == -1) {
		perror("bind");
		(void) close(soc);
		freeaddrinfo(res0);
		return -1;
	}
	if (listen(soc, SOMAXCONN) == -1) {
		perror("listen");
		(void) close(soc);
		freeaddrinfo(res0);
		return -1;
	}
	freeaddrinfo(res0);
	return soc;
}

