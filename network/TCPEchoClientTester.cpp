/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** EchoClientTester
*/

#include <iostream>
#include "ATCPConnection.hpp"

int main(int ac, const char *av[]) {
	if (ac != 2) {
		std::cerr << "TOCARD!!!\nUSAGE: ./client port" << std::endl;
		return (84);
	}

	bstd::network::TCPBasicEchoClient client(atoi(av[1]));

	client.run();
}