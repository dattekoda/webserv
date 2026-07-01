#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <map>
#include <string>
#include <vector>

struct Directive {
  std::vector<std::map<std::string, std::string> > map_;
  std::vector<std::vector<int> > ints_;
};

struct Config {
private:
  std::vector<std::string> v_;

public:
  Config(std::string const &content);
};

#endif
