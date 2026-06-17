#ifndef IEVENTHANDLER_HPP
#define IEVENTHANDLER_HPP

#include <stdint.h>

enum	HandleResult {
	HR_CONTINUE,
	HR_CLOSE
};

class IEventHandler {
public:
	virtual	~IEventHandler() {}

	virtual HandleResult	handleEvent(int fd, uint32_t events) = 0;
};

#endif
