#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

#include <stdint.h>

class IEventHandler {
public:
	virtual	~IEventHandler() {}

	virtual void	handleEvent(int fd, uint32_t events) = 0;
};

#endif
