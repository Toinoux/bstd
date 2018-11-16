/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** socketTester
*/

#include <iostream>
#include "TCPServer.hpp"

int main() {
	bstd::network::TCPServer<1> server;

	server.run([&server]{
		std::string msg;

		while (1) {
			SOCKADDR_IN csin = {0};
			SOCKET csock;
			size_t sinsize = sizeof csin;

			csock = server.getSocket().accept(server.getPort());
			msg = server.revc(csock, 0);
			std::cout << msg << std::endl;
		}
	});
}