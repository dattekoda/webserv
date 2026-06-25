#include <cerrno>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string.h>
#include <string>

class File {
private:
  std::string buff_;

public:
  File(const std::string &file_name) {
    std::ifstream ifs;

    try {
      ifs.open(file_name.c_str());
      if (!ifs)
        throw std::runtime_error(::strerror(errno));
      ifs.exceptions(std::ios::failbit | std::ios::badbit);
      buff_.assign(std::istreambuf_iterator<char>(ifs),
                   std::istreambuf_iterator<char>());
    } catch (const std::exception &e) {
      throw std::runtime_error(file_name + ": " + e.what());
    }
  }
  const std::string &getBuf(void) const { return buff_; }
};
