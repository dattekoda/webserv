/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 21:54:04 by khanadat          #+#    #+#             */
/*   Updated: 2026/06/14 23:04:52 by khanadat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "HttpMessage.hpp"
#include "IEventHandler.hpp"
#include "EventContext.hpp"
#include <sys/types.h>

#ifndef RECV_SIZE
#define RECV_SIZE	4096
#endif

enum	ConnState {
	CONN_WAIT,
	CONN_RECV,
	CONN_PARSE,
	CONN_EXEC,
	CONN_SEND
};

enum	ParseState {
	PARSE_START,
	PARSE_HEADER,
	PARSE_BODY,
	PARSE_TRAILER
};

enum	CGIState {
	CGI_INIT,
	CGI_WRITE,
	CGI_WAIT,
	CGI_READ,
	CGI_PARSE
};

enum	ChunkedState {
	CHUNK_SIZE,
	CHUNK_CRLF,
	CHUNK_DATA,
	CHUNK_TRAILER,
	CHUNK_END
};

enum	HandleResult {
	HR_CONTINUE,
	HR_CLOSE
};

class IEpollModifier;

class Connection : public IEventHandler {
private:
	EventContext		connCtx_;
	EventContext		cgiCtx_;

	IEpollModifier		*iem_;
	ConnState		state_;
	std::vector<char>	buffIn_;
	std::vector<char>	buffOut_;

	ParseState		pstate_;
	ChunkedState		chstate_;

	HttpRequest		req_;
	HttpResponse		res_;

	std::vector<char>	cgiBufIn_;
	std::vector<char>	cgiBufOut_;

	ssize_t	recv(void);
	void	parse(void);
	void	exec(void);
	ssize_t	send(void);

	Connection&	operator=(const Connection& others);
	Connection(const Connection& others);
public:
	Connection(int fd, IEpollModifier *iem);
	~Connection();
	HandleResult	handle(void);
};

#endif
