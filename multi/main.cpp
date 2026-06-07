#include <iostream>
#include "Server.hpp"

int	main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cerr << "set port num" << std::endl;
		return 1;
	}
	try {
		SocketFD	sfd(argv[1]);
		std::cerr << "ready for accept\n" << std::endl;
		Server	serv(sfd);
		// CycleManager.run();
	} catch (const std::runtime_error &e) {
		std::cerr << e.what();
		return 1;
	}
	return 0;
}

