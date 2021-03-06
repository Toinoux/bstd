/*
** EPITECH PROJECT, 2018
** tech3
** File description:
** UDPEchoClientTester
*/

#include "UDPSocket.hpp"

int main(int ac, const char *av[]) {
	if (ac != 3) {
		std::cerr << "TOCARD!!!\nUSAGE: ./client host port" << std::endl;
		return (84);
	}

	bstd::network::UDPBasicEchoClient client(av[1], atoi(av[2]));

	client.run();
}