#ifndef IEPOLLMODIFIER_HPP
#define IEPOLLMODIFIER_HPP

#include <stdint.h>
#include "EventContext.hpp"

class IEpollModifier {
public:
	virtual ~IEpollModifier();

	virtual int	epollAdd(EventContext *ctx, uint32_t event) = 0;
	virtual int	epollMod(EventContext *ctx, uint32_t event) = 0;
	virtual int	epollDel(int fd) = 0;
};

#endif
