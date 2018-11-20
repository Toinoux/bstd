/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** UDPEchoServerTester
*/

#include "UDPSocket.hpp"

int main() {
	bstd::network::UDPBasicEchoServer server(5000);

	server.run();
}