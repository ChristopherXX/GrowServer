#include "ENetServer.hpp"
#include "client/PlayerInfo.hpp"
#include "utils/Logger.hpp"

ENetServer::ENetServer(ENetAddress address)
{
	this->server = enet_host_create(&address, 1024, 2, 0, 0);
	if (this->server == NULL) {
		std::cout << "An error occurred while trying to create an ENet server host. " + std::to_string(address.host) + ':' + std::to_string(address.port) << std::endl;
		return;
	}
	this->server->checksum = enet_crc32;
	enet_host_compress_with_range_coder(this->server);
	Logger.Log("Server is now listening on port: " + std::to_string(address.port), LogType::LOG_TYPE_POSITIVE);
}

ENetServer::~ENetServer()
{
	enet_host_destroy(this->server);
}

void ENetServer::run()
{
	std::async(&ENetServer::eventsLoop, this).get();
}

void ENetServer::eventsLoop()
{
	while (true) {
		while (enet_host_service(this->server, &this->events, 1000) > 0) {
			auto peer = this->events.peer;
			switch (this->events.type) {
			case ENET_EVENT_TYPE_NONE:
				break;
			case ENET_EVENT_TYPE_CONNECT: {
				auto player = new PlayerInfo(peer, this);
				player->_events__OnConnect();
				break;
			}
			case ENET_EVENT_TYPE_DISCONNECT: {
				auto player = (PlayerInfo*)peer->data;
				player->_events__OnDisconnect();
				break;
			}
			case ENET_EVENT_TYPE_RECEIVE: {
				auto player = (PlayerInfo*)peer->data;
				player->_events__OnReceive(this->events.packet);
				enet_packet_destroy(this->events.packet);
				break;
			}
			}
		}
	}
}