#include "Config.hpp"
#include <fstream>
#include <string>

Config *parse_config(const std::string &config_file) {
  std::fstream f;

  f.open(config_file.c_str());
  if (!f)
    throw std::runtime_error("open() failed");
  return Config(f);
}
