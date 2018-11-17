/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** socketTester
*/

#include <iostream>
#include "TCPServer.hpp"

int main() {
	bstd::network::BasicEchoServer server;

	server.run();
}