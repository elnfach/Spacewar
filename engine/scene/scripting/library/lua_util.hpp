//
// Created by elnfach on 20.04.2025.
//

#ifndef LUA_UTIL_HPP
#define LUA_UTIL_HPP
#include "SFML/System/Vector2.hpp"

/*inline int push_vec2f(lua_State* p_state, const sf::Vector2f& p_vec)
{
	lua_createtable(p_state, 2, 0);
	lua_pushnumber(p_state, p_vec.x);
	lua_rawseti(p_state, -2, 1);
	lua_pushnumber(p_state, p_vec.y);
	lua_rawseti(p_state, -2, 2);
	return 1;
}

inline sf::Vector2f to_vec2f(lua_State* p_state, const int p_id)
{
	lua_pushvalue(p_state, p_id);
	if (!lua_istable(p_state, p_id) && lua_rawlen(p_state, p_id) < 2)
		return {};
	lua_rawgeti(p_state, -1, 1);
	const float x = lua_tonumber(p_state, -1);
	lua_pop(p_state, 1);
	lua_rawgeti(p_state, -1, 2);
	const float y = lua_tonumber(p_state, -1);
	lua_pop(p_state, 1);
	lua_pop(p_state, 1);
	return {x, y};
}*/

#endif //LUA_UTIL_HPP
