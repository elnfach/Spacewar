//
// Created by elnfach on 23.04.2025.
//

#include "lua_screen_system.hpp"

#include "get_entity.hpp"
#include "lua_util.hpp"
#include "config/engine.hpp"
#include "scene/main/scene_tree.hpp"
#include "scene/networking/network_engine.hpp"

static int get_window_size(lua_State *p_state) {
	//return push_vec2f(p_state, sf::Vector2f(spacewar::scene_tree::get_current_scene()->get_viewport_size()));
}

static constexpr luaL_Reg scene[] = {
	{"GetSize",get_window_size},
	{nullptr, nullptr}
};

static int input_lib_require(lua_State* p_state) {
	luaL_newlib(p_state, scene);
	return 1;
}

void lua_screen_system(lua_State* p_state)
{
	luaL_requiref(p_state, "Screen", input_lib_require, 1);
	lua_pop(p_state, 1);
}
