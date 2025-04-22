//
// Created by elnfach on 20.04.2025.
//

#ifndef NETWORK_ENGINE_HPP
#define NETWORK_ENGINE_HPP
#include "protocol.hpp"

namespace spacewar
{
	class network_engine final {
	public:
		static void initialize();
		static void finalize();
	private:

	public:
		static void start_server();
		static void stop_server();
		static void server_send_data(const position& p_position);

		static void start_client();
		static void stop_client();
		static void listen();
		static void client_send_data(const position& p_position);
	};
}



#endif //NETWORK_ENGINE_HPP
