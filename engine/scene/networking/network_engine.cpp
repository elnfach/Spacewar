//
// Created by elnfach on 20.04.2025.
//

#include "network_engine.hpp"

#include "ahxrwinsock/ahxrwinsock.h"
#include "scene/scripting/script_engine.hpp"

struct network_data
{
	AHXRSERVER server;
	AHXRCLIENT client;
	SOCKET client_socket;
};
static network_data* s_network_data = nullptr;

void on_client_disconnected(SOCKET clientSocket, addrinfo* addressInf)
{
	spacewar::script_engine::invoke_function(3, "OnServerClientDisconnected", nullptr);
}

void on_client_connected(SOCKET clientSocket, addrinfo* addressInf)
{
	s_network_data->client_socket = clientSocket;
	spacewar::script_engine::invoke_function(3, "OnServerClientConnected", nullptr);
}

void spacewar::network_engine::initialize()
{
	s_network_data = new network_data();
}

void spacewar::network_engine::finalize()
{
	delete s_network_data;
	s_network_data = nullptr;
}

void onServerReceiveData(SOCKET clientSocket, CLIENTDATA info, char * data)
{
	position pos{};
	memcpy(&pos, data, sizeof(position));
	std::cout << "player: " << pos.x << ", " << pos.y << std::endl;
}

void spacewar::network_engine::start_server()
{
	s_network_data->server.start_server("666", TCP_SERVER, on_client_connected, on_client_disconnected, onServerReceiveData);
}

void spacewar::network_engine::stop_server()
{
}

void onClientConnect() {

}

void spacewar::network_engine::start_client()
{
	s_network_data->client.init("127.0.0.1", "666", TCP_SERVER, onClientConnect);
	listen();
}

void spacewar::network_engine::stop_client()
{
}

void on_client_receive_data( char * data )
{
	position pos{};
	memcpy(&pos, data, sizeof(position));
	const auto scene = spacewar::script_engine::get_context_scene()->get_object_by_uuid(1);

	auto& [position, rotation, scale] = scene.get_component<spacewar::TransformComponent>();
	position = sf::Vector2f{ pos.x, pos.y };
	rotation = pos.rotation;
	//spacewar::script_engine::invoke_function(1, "OnClientReceiveData", nullptr);
}

void spacewar::network_engine::listen()
{
	std::cout << "listening..." << std::endl;
	s_network_data->client.listen(on_client_receive_data, true);
}

void spacewar::network_engine::client_send_data(const position& p_position)
{
	s_network_data->client.send_data(reinterpret_cast<const char*>(&p_position));
}

void spacewar::network_engine::server_send_data(const position& p_position)
{
	s_network_data->server.send_data(s_network_data->client_socket, reinterpret_cast<const char*>(&p_position));
}
