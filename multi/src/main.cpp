#include <iostream>
#include "Server.hpp"
#include "Config.hpp"

int	main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cerr << "set correct file" << std::endl;
		return 1;
	}
	try {
		Config *c = new Config();
		loadConfig(argv[1], c);
		Server	serv(c);
		std::cerr << "ready for accept!" << std::endl;
		serv.run();
	} catch (const std::runtime_error &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}

