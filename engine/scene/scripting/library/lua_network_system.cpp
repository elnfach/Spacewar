//
// Created by elnfach on 20.04.2025.
//

#include "lua_network_system.hpp"

#include "lua_util.hpp"
#include "scene/networking/network_engine.hpp"
#include "SFML/System/Vector2.hpp"

static int receive_data(lua_State* p_state)
{
	
	return 1;
}

static int send_data(lua_State* p_state) {
	const sf::Vector2f pos = to_vec2f(p_state, 1);
	const float rotation = lua_tonumber(p_state, 2);
	const position data = { pos.x, pos.y, rotation };
	spacewar::network_engine::server_send_data(data);
	return 0;
}

static int create_client(lua_State* p_state) {
	spacewar::network_engine::start_client();
	return 0;
}

static int create_server(lua_State* p_state) {
	spacewar::network_engine::start_server();
	return 0;
}

static constexpr luaL_Reg network[] = {
	{"CreateServer",create_server},
	{"CreateClient",create_client},
	{"SendData",send_data},
	{nullptr, nullptr}
};

static int input_lib_require(lua_State* p_state) {
	luaL_newlib(p_state, network);
	return 1;
}

void load_network_system_init(lua_State* p_state)
{
	luaL_requiref(p_state, "Network", input_lib_require, 1);
	lua_pop(p_state, 1);
}
