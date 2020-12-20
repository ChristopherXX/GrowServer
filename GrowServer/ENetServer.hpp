#pragma once
#ifndef ENETSERVER_HPP
#define ENETSERVER_HPP

#include "enet/include/enet.h"
#include <future>
#include <iostream>
#include <string>

class ENetServer
{
public:
	ENetEvent events;
	ENetHost* server;

	ENetServer(ENetAddress);
	~ENetServer();

	void run();
	void eventsLoop();
};
#endif