//
// Created by elnfach on 20.04.2025.
//

#ifndef LUA_UTIL_HPP
#define LUA_UTIL_HPP
#include "lua/lua.hpp"
#include "SFML/System/Vector2.hpp"

inline int push_vec2f(lua_State* p_state, const sf::Vector2f& vec)
{
	lua_createtable(p_state, 2, 0);
	lua_pushnumber(p_state, vec.x);
	lua_rawseti(p_state, -2, 1);
	lua_pushnumber(p_state, vec.y);
	lua_rawseti(p_state, -2, 2);
	return 1;
}

inline sf::Vector2f to_vec2f(lua_State* p_state, int p_id)
{
	lua_pushvalue(p_state, p_id);
	if (!lua_istable(p_state, p_id) && lua_rawlen(p_state, p_id) < 2)
		throw lua_error(p_state);
	lua_rawgeti(p_state, -1, 1);
	const auto x = lua_tonumber(p_state, -1);
	lua_pop(p_state, 1);
	lua_rawgeti(p_state, -1, 2);
	const auto y = lua_tonumber(p_state, -1);
	lua_pop(p_state, 1);
	lua_pop(p_state, 1);
	return sf::Vector2f(x, y);
}

#endif //LUA_UTIL_HPP
