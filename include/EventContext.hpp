#ifndef EVENTCONTEXT_HPP
#define EVENTCONTEXT_HPP

class IEpollHandler;

class EventContext {
  int fd_;
  IEpollHandler *handler_;
};

#endif
