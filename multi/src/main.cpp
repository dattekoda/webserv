#include "Config.hpp"
#include "EpollFd.hpp"
#include "File.hpp"
#include "SockFd.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

#define LISTEN_SIZE 30
#define EVENT_SIZE 20

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "set file" << std::endl;
    return 1;
  }
  try {
    File f(argv[1]);
    Config c(f.getBuf());
  } catch (const std::exception &e) {
    std::cerr << argv[0] << ": " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
