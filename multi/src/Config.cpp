#include "Config.hpp"
#include <stdexcept>
#include <fstream>
#include <errno.h>
#include <string.h>

void	loadConfig(const std::string &file_name, struct Config *conf) {
	std::ifstream	ifs(file_name.c_str());

	if (!ifs.is_open())
		throw (std::runtime_error(file_name + ": " + ::strerror(errno)));
	std::string	pstr;
	while (ifs >> pstr) {
		ServerConfig	server;
		server.host_.port_ = pstr;
		conf->servers_.push_back(server);
	}
	ifs.close();
}

