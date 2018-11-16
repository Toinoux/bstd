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
	template <size_t CONNECTION_MAX>
	class TCPServer {
	public:
		TCPServer() : _socket(SOCK_STREAM), _port(_socket.bind()){
			_socket.listen(CONNECTION_MAX);
			std::cout << "Listening on port " << _port << ":" << std::endl;
		};

	public:
		void send(SOCKET sock, std::string_view buffer, size_t len, int flags = 0) const {
			if (::send(sock, buffer.data(), len, flags) < 0)
				std::cerr << "Send() failed" << std::endl;
		};

		void sendAll(std::string_view buffer, size_t len, int flags = 0) const {
			for (auto client : (*_clients)) {
				this->send(client, buffer, len, flags);
			}
		}

		const std::string revc(SOCKET sock, int flags = 0) const {
			char buffer[READ_SIZE] = {0};
			std::string str;
			int len;

			while ((len = ::recv(sock, buffer, READ_SIZE - 1, flags))) {
				if (len < 0)
					std::cerr << "Recv() failed" << std::endl;
				buffer[len] = 0;
				str += buffer;
			}
			return str;
		};

		template <typename Functor>
		void run(Functor &&f) {
			f();
		}

	public:
		PORT getPort() const {
			return _port;
		};

		const Socket &getSocket() const {
			return _socket;
		}

		SOCKET getSocketValue() const {
			return _socket.getSocket();
		}

		const std::unique_ptr<std::array<SOCKET, CONNECTION_MAX>> &getClients() const {
			return _clients;
		}

	private:
		std::unique_ptr<std::array<SOCKET, CONNECTION_MAX>> _clients;
		Socket _socket;
		PORT _port;

	private:
		static inline const int READ_SIZE = 4096;
	};
}
