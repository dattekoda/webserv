#ifndef SERVER_HPP
#define SERVER_HPP

struct Config {};

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
public:
  Server(const Config *config);
};

#endif
