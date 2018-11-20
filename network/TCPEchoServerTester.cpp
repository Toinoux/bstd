/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** socketTester
*/

#include <iostream>
#include "TCPSocket.hpp"

int main() {
	bstd::network::TCPBasicEchoServer server(1, 5000);

	server.run();
}