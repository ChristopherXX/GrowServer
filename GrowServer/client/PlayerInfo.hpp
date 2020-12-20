#pragma once
#ifndef PLAYERINFO_HPP
#define PLAYERINFO_HPP

#include "../enet/include/enet.h"
#include "../ENetServer.hpp"
#include "../BinaryWriter.hpp"

class PlayerInfo 
{
public:
	ENetPeer* peer;
	ENetServer* _server;
	PlayerInfo(ENetPeer*, ENetServer*);

	void _events__OnConnect();
	void _events__OnDisconnect();
	void _events__OnReceive(ENetPacket*);

	void send(uint8_t*, size_t);
	void send_hello_packet();

	bool operator==(PlayerInfo* right) {
		return this->peer->host->address.host == right->peer->host->address.host;
	}
};
#endif
