#include "PlayerInfo.hpp"
#include "../proton/enums.hpp"

PlayerInfo::PlayerInfo(ENetPeer* Peer, ENetServer* server) {
	this->peer = Peer;
	this->_server = server;
}

void PlayerInfo::_events__OnConnect() {
	auto localhost = 0;
	for (auto peers = _server->server->peers;
		peers < &_server->server->peers[_server->server->peerCount];
		++peers)
	{
		if (peers->state != ENET_PEER_STATE_CONNECTED)
			continue;
		if (peers->address.host == peer->address.host)
			localhost++;
		if (localhost > 3)
		{
			//TODO: block connections
			return;
		}
	}
	this->send_hello_packet();
}
void PlayerInfo::_events__OnDisconnect() {}
void PlayerInfo::_events__OnReceive(ENetPacket* packet) {
	auto data = packet->data;
	auto type = packet->dataLength > (unsigned int)3U ? (E_NETMESSAGE_TYPES)*data : (E_NETMESSAGE_TYPES)0;
	switch (type) {
		case E_NETMESSAGE_TYPES::NET_MESSAGE_UNKNOWN:
			break;
		case E_NETMESSAGE_TYPES::NET_MESSAGE_GENERIC_TEXT:
		case E_NETMESSAGE_TYPES::NET_MESSAGE_GAME_MESSAGE:
		{
			break;
		}
		case E_NETMESSAGE_TYPES::NET_MESSAGE_GAME_PACKET:
		{
			break;
		}
		default:
			break;
	}
}

void PlayerInfo::send(uint8_t* data, size_t len) {
	if (this->peer != NULL && this->peer->state == ENET_PEER_STATE_CONNECTED) {
		auto packet = enet_packet_create(data, len, 0);
		enet_peer_send(peer, 0, packet);
	}
}
void PlayerInfo::send_hello_packet() {
	BinaryWriter bw(4);
	bw.write(1);
	this->send(bw.data, 4);
}