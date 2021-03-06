#include <winsock2.h>
#include <ws2tcpip.h>
#include "ISocket.hpp"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma once
#pragma comment(lib, "ws2_32.lib")

namespace bstd::network {
	static const char *DEFAULT_HOST = "localhost";

	class Socket : public ISocket {
	public:

	public:
		Socket() = delete;
		Socket(int theType, int protocol = 0) : _socket(socket(AF_INET, theType, protocol)) {
			if (_socket == -1)
				throw std::runtime_error("creatSocket failed");
			char i = 1;
			if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(int)) < 0)
				throw std::runtime_error("setsocket opt failed (FUCK LE KERNEL)");
			WSADATA WSAData;
			WSAStartup(MAKEWORD(2, 0), &WSAData);
		};

		PORT bind(PORT port = 0) const {
			SOCKADDR_IN sin = { 0 };
			socklen_t len = sizeof(sin);

			sin.sin_addr.s_addr = htonl(INADDR_ANY);
			sin.sin_family = AF_INET;
			sin.sin_port = htons(port);

			if (::bind(_socket, (sockaddr *)&sin, sizeof(sin)) == -1)
				throw std::runtime_error("bind failed");
			if (getsockname(_socket, (struct sockaddr *)&sin, &len) == -1)
				throw std::runtime_error("getsockname failed");
			return ntohs(sin.sin_port);
		};

		void listen(int nbConnections) const {
			if (::listen(_socket, nbConnections) == -1)
				throw std::runtime_error("listenfailed");
		};

		SOCKET accept(PORT port) const {
			SOCKADDR_IN csin = { 0 };
			SOCKET client;
			socklen_t crecsize = sizeof(csin);

			client = ::accept(_socket, (sockaddr *)&csin, &crecsize);
			if (client == -1)
				throw std::runtime_error("accept failed");
			return client;
		};

		void connect(PORT port, std::string const &host = DEFAULT_HOST) const {
			struct hostent *hostinfo;
			SOCKADDR_IN sin = { 0 };

			hostinfo = gethostbyname(host.c_str());
			if (hostinfo == NULL) {
				throw std::runtime_error("Unknow host");
			}
			sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr;
			sin.sin_port = htons(port);
			sin.sin_family = AF_INET;
			if ((::connect(_socket, (sockaddr *)&sin, sizeof(sin))) == -1)
				throw std::runtime_error("connect failed");
		};

		void close() const {
			WSACleanup();
		};

	public:
		SOCKET getSocket() const {
			return _socket;
		};

	public:
		SOCKET _socket;

	public:
		~Socket() {
			WSACleanup();
		};
	};
}
