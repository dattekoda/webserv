#include "EpollFD.hpp"
#include <vector>
#include <string>
#include <aio.h>
#include <sys/epoll.h>

class SocketFD;
struct Config;
struct ClientContext;

using namespace	std;

class CycleManager {
private:
	const Config*		_conf;
	vector<SocketFD*>	_socketFDs;

	EpollFD			_epollFD;
	epoll_event		*_ev;

	bool			isSocketFDs(int fd);

	CycleManager& operator=(const CycleManager &others);
	CycleManager(const CycleManager &others);

	void	handleErrors(void);
	void	handleActions(int nfds);

	void	handleConnect(ClientContext *cctx);
	void	handleHttp(ClientContext *cctx);
public:
	CycleManager();
	CycleManager(Config& conf);

	void	loadConf(const char *file_name);
	void	begin(void);
};

typedef enum {
	STATE_READ_REQLINE,
	STATE_READ_HEADER,
	STATE_READ_BODY,

	STATE_PROCESS_REQ,
	STATE_CGI_READ_RES,
	STATE_CGI_WRITE_BODY,

	STATE_WRITE_RES,
	STATE_CLOSE
}	ClientState;

typedef enum {
	CTX_LISTEN_SOCKET,
	CTX_CLIENT_SOCKET,
	CTX_CGI_PIPE
}	ContextType;

struct BaseContext {
	int		_fd;
	ContextType	_ctx;
	virtual		~BaseContext() {}
};

struct ClientContext : public BaseContext {
	ClientState	_state;
	vector<char>	_buf;
	vector<char>	_cgi_res_buf;
	size_t		_buffer_len;
	size_t		_content_length;

	pid_t		_cgi_pid;
	int		_cgi_in_fd;
	int		_cgi_out_fd;
};

struct CgiContext : public BaseContext {
	ClientContext*	_client_ctx;
	bool		_is_read_pipe;
};

int	main(int argc, char *argv[]) {
	CycleManager	cm;

	cm.loadConf(argv[1]);
	cm.begin();
	return 0;
}

void	CycleManager::begin(void) {
	int	nfds;

	for (;;) {
// Specifying a timeout of -1
// causes epoll_wait() to block indefinitely,
// while specifying a timeout equal to zero
// cause epoll_wait() to return immediately,
// even if no events are available.
		switch (nfds = _epollFD.wait(_ev, -1)) {
			case -1:
				handleErrors();
				break ;
			default:
				handleActions(nfds);
				break ;
		}
	}
}

void	CycleManager::handleActions(int nfds) {
	for(int i = 0; i < nfds; ++i) {
		ClientContext	*cctx \
		= static_cast<ClientContext*>(_ev[i].data.ptr);
		if (isSocketFDs(cctx->_fd))
			handleConnect(cctx);
		else
			handleHttp(cctx);
	}
}

