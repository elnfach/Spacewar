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

void on_client_disconnected(SOCKET p_client_socket, addrinfo* p_address_info)
{
	spacewar::script_engine::invoke_function(3, "OnServerClientDisconnected");
}

void on_client_connected(SOCKET p_client_socket, addrinfo* p_address_info)
{
	s_network_data->client_socket = p_client_socket;
	spacewar::script_engine::invoke_function(3, "OnServerClientConnected", p_client_socket);
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

void on_server_receive_data(SOCKET p_client_socket, CLIENTDATA p_info, char * p_data)
{
	position pos{};
	memcpy(&pos, p_data, sizeof(position));

}

void spacewar::network_engine::start_server(const std::string_view& p_port)
{
	s_network_data->server.start_server(p_port.data(), TCP_SERVER, on_client_connected, on_client_disconnected, on_server_receive_data);
}

void spacewar::network_engine::stop_server()
{
}

void on_client_connected() {

}

void spacewar::network_engine::start_client(const std::string_view& p_ip_address, const std::string_view& p_port)
{
	s_network_data->client.init(p_ip_address.data(), p_port.data(), TCP_SERVER, on_client_connected);
	listen();
}

void spacewar::network_engine::stop_client()
{
}

void on_client_receive_data(char * p_data)
{
	position pos{};
	memcpy(&pos, p_data, sizeof(position));
	spacewar::script_engine::invoke_function(3, "OnClientReceiveData", sf::Vector2f(pos.x, pos.y), pos.rotation);
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
