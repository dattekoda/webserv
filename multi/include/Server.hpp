#ifndef SERVER_HPP
#define SERVER_HPP

class IEpollManager {
private:
  int efd_;

public:
  virtual ~IEpollManager() = 0;
  void add(int sfd);
  void del(int sfd);
  int wait(void);
};

class Server : public IEpollManager {
  const Config *config_;

public:
  Server(const Config *config) : config_(config){};
};

#endif
