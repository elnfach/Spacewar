//
// Created by elnfach on 20.04.2025.
//

#include "network_engine.hpp"

#include "ahxrwinsock/ahxrwinsock.h"
#include "scene/scripting/script_engine.hpp"
#include "SFML/System/Vector2.hpp"

struct network_data
{
	AHXRSERVER server;
	AHXRCLIENT client;
	SOCKET client_socket;
};
network_data* s_data = nullptr;

void on_client_disconnected(SOCKET p_client_socket, addrinfo* p_address_info)
{
	//spacewar::script_engine::invoke_function(3, "OnServerClientDisconnected");
}

void on_client_connected(SOCKET p_client_socket, addrinfo* p_address_info)
{
	//s_network_data->client_socket = p_client_socket;
	//spacewar::script_engine::invoke_function(3, "OnServerClientConnected", p_client_socket);
}

void on_server_receive_data(SOCKET p_client_socket, CLIENTDATA p_info, char * p_data)
{
	position pos{};
	memcpy(&pos, p_data, sizeof(position));
}

spacewar::network_engine& spacewar::network_engine::get_instance()
{
	static network_engine s_engine;
	return s_engine;
}

spacewar::network_engine::network_engine()
{
	s_data = new network_data;
}

spacewar::network_engine::~network_engine()
{
	delete s_data;
}

void spacewar::network_engine::start_server(const std::string_view& p_port)
{
	s_data->server.start_server(p_port.data(), TCP_SERVER, on_client_connected, on_client_disconnected, on_server_receive_data);
}

void spacewar::network_engine::stop_server()
{
}

void on_client_connected() {

}

void spacewar::network_engine::start_client(const std::string_view& p_ip_address, const std::string_view& p_port)
{
	s_data->client.init(p_ip_address.data(), p_port.data(), TCP_SERVER, on_client_connected);
	listen();
}

void spacewar::network_engine::stop_client()
{
}

void on_client_receive_data(char * p_data)
{
	position pos{};
	memcpy(&pos, p_data, sizeof(position));
	//spacewar::script_engine::invoke_function(3, "OnClientReceiveData", sf::Vector2f(pos.x, pos.y), pos.rotation);
}

void spacewar::network_engine::listen()
{
	std::cout << "listening..." << std::endl;
	s_data->client.listen(on_client_receive_data, true);
}

void spacewar::network_engine::client_send_data(const sf::Vector2f& p_position, const float_t rotation, const sf::Vector2f& p_scale)
{
	position pos{};
	pos.x = 50;
	pos.y = 50;
	pos.rotation = 0;
	s_data->client.send_data(reinterpret_cast<const char*>(&pos));
}

void spacewar::network_engine::server_send_data(const position& p_position)
{
	s_data->server.send_data(s_data->client_socket, reinterpret_cast<const char*>(&p_position));
}
