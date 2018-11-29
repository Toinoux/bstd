/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** UDPSocket
*/

#ifdef _WIN32
	#include "WinSocket.hpp"
#else
	#include "UnixSocket.hpp"
#endif

#include <string_view>
#include <iostream>
#include <string>

#pragma once

namespace bstd::network {
	class UDPSocket : public Socket {
	public:
		UDPSocket() : Socket(SOCK_DGRAM) {
		};

		UDPSocket(PORT port) : Socket(SOCK_DGRAM), _port(bind(port)) {
		};


	public:
		std::string recvfrom(SOCKET sock, SOCKADDR_IN *sin = NULL,int flags = 0) const{
			int sinsize = sizeof(*sin);
			char buffer[READ_SIZE];
			std::string msg;
			int len;

			if ((len = ::recvfrom(sock, buffer, READ_SIZE - 1, flags, (SOCKADDR *)sin, &sinsize)) < 0) {
				std::cerr << "recvfrom failed" << std::endl;
			} else {
				buffer[len] = 0;
				msg = buffer;
			}
			return msg;
		};

		void sendto(SOCKET sock, std::string_view buffer, std::string_view host = DEFAULT_HOST, PORT port = 80, int flags = 0) const {
			struct hostent *hostinfo;
			SOCKADDR_IN sin = {0};

			if ((hostinfo = ::gethostbyname(host.data())) == NULL) {
				std::cerr << "Unknown host " << host << std::endl;
				return;
			}

			sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr;
   			sin.sin_port = htons(port);
   			sin.sin_family = AF_INET;

			if(::sendto(sock, buffer.data(), buffer.size(), flags, (SOCKADDR *)&sin, sizeof(sin)) < 0)
				std::cerr << "Sendto() failed" << std::endl;
		};
	public:
		PORT getPort() const {
			return (_port);
		};

		virtual ~UDPSocket() {};

	private:
		PORT _port;

	private:
		static inline const int READ_SIZE = 4096;
	};

	class UDPBasicEchoServer : UDPSocket {
	public:
		UDPBasicEchoServer(PORT port = 0) : UDPSocket(port) {
			std::cout << "UDP Server listening on port " << getPort() << ":" << std::endl;
		};

		void run() {
			std::string msg;
			SOCKADDR_IN sin = {0};

			while (1) {
				msg = recvfrom(getSocket(), &sin);
				if (!msg.empty())
					std::cout << msg << std::endl;
			}
		};

		~UDPBasicEchoServer() {};
	};

	class UDPBasicEchoClient : UDPSocket {
	public:
		UDPBasicEchoClient() : UDPSocket() {};
		UDPBasicEchoClient(std::string_view dest, PORT port = 5000) : UDPSocket(), _dest(dest), _destPort(port) {
		};

		void run() {
			std::string msg;

			while (1) {
				std::getline(std::cin, msg);
				sendto(getSocket(), msg, _dest, _destPort);
			}
		}

	public:
		void setDest(std::string_view str) {
			_dest = str;
		};

		void setDestPort(PORT port) {
			_destPort = port;
		}

	public:
		~UDPBasicEchoClient() {};

	private:
		std::string _dest;
		PORT _destPort;
	};
}