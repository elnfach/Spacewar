//
// Created by elnfach on 29.04.2025.
//

#ifndef SESSION_HPP
#define SESSION_HPP
#include <memory>
#include <queue>
#include <unordered_map>
#include <vector>

#include "network_package.hpp"
#include "player.hpp"

namespace spacewar
{
	class session {
	public:
		session() = default;
		~session() = default;
	private:
		void stop_session();
	public:
		void start_session(const std::string_view& p_port);
		void connect_session(const std::string_view& p_address, const std::string_view& p_port);

		void update();
	private:
		//std::unordered_map<std::string, SOCKET> m_players;
		std::queue<network_package> m_data;
	};
}



#endif //SESSION_HPP
