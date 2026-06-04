#include <vector>
#include <string>
#include <map>

using namespace	std;

struct	Redirect;
struct	Uri;
struct	Location;

struct ConfigParams {
	string			root_;
	string			index_;

	map<string, string>	errorPages_;
	map<string, string>	acceptableCgi_;
	// e.g { "php", "/bin/php" }

	int			maxBodySize_;
	bool			isAbleToDirListing_;

	map<string, Redirect>	redirects_;
	// e.g redirects["/foo/bar.html"] = Redirect{"301", {"http://example.com/foo/"}}
};

struct Host {
	string	name_;
	string	addr_;
	string	port_;
};

struct Uri {
	string	path_;
};

struct Redirect {
	string	status_;
	Uri	uri_;
};

struct Config {
	Host			host_;
	ConfigParams		params_;
	vector<Location>	locations_;
};

struct ServerConfig {
	Host			host_;
	ConfigParams		params_;
	vector<Location>	locations_;
};

struct Location {
	string			path_;
	vector<Method>		methods_;
	ConfigParams		params_;
	vector<Location>	locations_;
};

