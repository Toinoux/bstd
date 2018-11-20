/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** TCPServer
*/

#ifdef _WIN32
	#include "WinSocket.hpp"
#else
	#include "UnixSocket.hpp"
#endif

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <array>

#pragma once

namespace bstd::network {
	class TCPSocket : public Socket {
	public:
		TCPSocket(size_t CONNECTION_MAX = 1) : Socket(SOCK_STREAM), _port(bind()) {
			listen(CONNECTION_MAX);
		}

		TCPSocket(PORT port, const std::string &host = DEFAULT_HOST) : Socket(SOCK_STREAM) {
			if (port != 0) {
				connect(port, host);
				std::cout << "Connected to " << host << ":" << port << std::endl;
			}
		}

	public:
		void send(SOCKET sock, std::string_view buffer, size_t len, int flags = 0) const {
			if (::send(sock, buffer.data(), len, flags) < 0)
				std::cerr << "Send() failed" << std::endl;
		};

		const std::string revc(SOCKET sock, int flags = 0) const {
			char buffer[READ_SIZE] = {0};
			std::string str;
			int len;

			while ((len = ::recv(sock, buffer, READ_SIZE - 1, flags))) {
				if (len < 0)
					std::cerr << "Recv() failed" << std::endl;
				buffer[len] = 0;
				str += buffer;
				if (len < READ_SIZE - 1)
					break;
			}
			return str;
		};

		PORT getPort() const {
			return (_port);
		}

		virtual ~TCPSocket() {};

	private:
		PORT _port;

	private:
		static inline const int READ_SIZE = 4096;
	};

	class TCPBasicEchoServer : public TCPSocket {
	public:
		TCPBasicEchoServer(size_t CONNECTION_MAX = 1, bool verbose = true) : TCPSocket(CONNECTION_MAX) {
			if(verbose)
				std::cout << "Listening on port " << getPort() << ":" << std::endl;
		};

		void run() {
			std::string msg;

			while (1) {
				SOCKET csock;

				csock = this->accept(getPort());
				while(1) {
					msg = this->revc(csock);
					std::cout << msg << std::endl;
					if (msg.size() == 0) {
						std::cout << "LE CLIENT EST MORT :(" << std::endl << "BYE BYE" << std::endl;
						break;
					}
				}
			}
		}

		~TCPBasicEchoServer() {};
	};

	class TCPBasicEchoClient : public TCPSocket {
	public:
		TCPBasicEchoClient(PORT port, const std::string &host = DEFAULT_HOST) : TCPSocket(port, host) {
		};

		void run() {
			std::string msg;

			while (1) {
				std::getline(std::cin, msg);
				send(getSocket(), msg, msg.size());
			}
		}

		~TCPBasicEchoClient() {};
	};
}
