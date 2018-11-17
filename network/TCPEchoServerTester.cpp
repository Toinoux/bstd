/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** socketTester
*/

#include <iostream>
#include "ATCPConnection.hpp"

int main() {
	bstd::network::TCPBasicEchoServer server;

	server.run();
}