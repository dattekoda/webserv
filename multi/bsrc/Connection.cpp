#include "Connection.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdexcept>

Connection::Connection(int fd) : fd_(fd), state_(CONN_WAIT){
	buffIn_.reserve(RECV_SIZE);
}

Connection::~Connection() {}

ssize_t	Connection::recv(void) {
	char		buf[RECV_SIZE];
	const ssize_t	retRecv = ::recv(fd_, buf, RECV_SIZE, 0);

	if (retRecv < 0)
		throw std::runtime_error("recv() failed");
	if (0 < retRecv)
		buffOut_.insert(buffOut_.end(), buf, buf + retRecv);
	return retRecv;
}

// HandleResult	Connection::handle(void) {
// }

// ssize_t	Connection::send(void) {
// 	::send(fd_, buffOut_.data(), 
// }

