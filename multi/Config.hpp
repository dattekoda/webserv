#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <vector>
# include <string>

struct	ServerConfig;
struct	Host;

struct	Config {
	std::vector<ServerConfig>	servers_;
};

struct	Host {
	std::string	name_;
	std::string	addr_;
	std::string	port_;
};

struct	ServerConfig {
	Host	host_;
};

#endif

