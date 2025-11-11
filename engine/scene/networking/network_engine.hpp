//
// Created by elnfach on 20.04.2025.
//

#ifndef NETWORK_ENGINE_HPP
#define NETWORK_ENGINE_HPP
#include <cmath>
#include <string_view>

#include "components/protocol.hpp"
#include "SFML/System/Vector2.hpp"

namespace spacewar
{
	class network_engine final {
	public:

		static network_engine& get_instance();
	private:
		network_engine();
		~network_engine();
	public:
		void start_server(const std::string_view& p_port);
		void stop_server();
		void server_send_data(const position& p_position);

		void start_client(const std::string_view& p_ip_address, const std::string_view& p_port);
		void stop_client();
		void listen();
		void client_send_data(const sf::Vector2f& p_position, const float_t rotation, const sf::Vector2f& p_scale);
	private:
	};
}



#endif //NETWORK_ENGINE_HPP
