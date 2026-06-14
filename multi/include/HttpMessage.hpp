#ifndef HTTPMESSAGE_HPP
#define HTTPMESSAGE_HPP

#include <map>
#include <string>
#include <vector>

enum MethodType {
	MTYPE_GET,
	MTYPE_POST,
	MTYPE_DEL
};

struct HttpMessage {
	std::string				version_;
	std::map<std::string, std::string>	headers_;
	std::vector<char>			body_;
};

struct HttpRequest : public HttpMessage {
	MethodType				mtype_;
	std::string				target_;
};

struct HttpResponse : public HttpMessage {
	std::string				status_;
	std::string				reason_;
};

#endif
