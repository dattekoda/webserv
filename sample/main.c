#include <stdio.h>
#include <unistd.h>

int	server_socket(const char *portnm);
void	accept_loop(int soc);

int	main(int argc, char *argv[]) {
	int	soc;

	if (argc == 1) {
		(void) fprintf(stderr, "%s port\n", argv[0]);
		return 1;
	}
	if ((soc = server_socket(argv[1])) == -1) {
		(void) fprintf(stderr, "server_socket(%s):error\n", argv[1]);
		return 1;
	}
	(void) fprintf(stderr, "ready for accept\n");

	accept_loop(soc);

	(void) close(soc);
	return 0;
}

