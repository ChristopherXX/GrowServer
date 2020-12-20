#include "enet/include/enet.h"
#include <csignal>
#include <future>
#include <iostream>
#include "ENetServer.hpp"

ENetServer* server;

void exitHandler(int s)
{
	delete server;
	exit(EXIT_FAILURE);
}

int main()
{
	signal(SIGINT, exitHandler);

	enet_initialize();
	if (server == NULL) {
		ENetAddress address;
		enet_address_set_host(&address, "0.0.0.0");
		address.port = 17091;
		server = new ENetServer(address);
		server->run();
	}
}