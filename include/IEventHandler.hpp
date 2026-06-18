#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

#include <stdint.h>

enum	EventResult {
	EV_CONTINUE,
	EV_CLOSE
};

class IEventHandler {
public:
	virtual	~IEventHandler() {}
	virtual EventResult	handleEvent(int fd, uint32_t events) = 0;
};

#endif

