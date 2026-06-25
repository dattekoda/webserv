#ifndef EVENTCONTEXT_HPP
#define EVENTCONTEXT_HPP

class IEventHandler;

struct EventContext {
	int		fd_;
	IEventHandler	*handler_;
};

#endif

