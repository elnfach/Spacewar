//
// Created by elnfach on 19.04.2025.
//

#include "lua_input_system.hpp"

#include <iostream>
#include <optional>

#include "get_entity.hpp"
#include "input/input.hpp"
#include "SFML/Window/Keyboard.hpp"

static int key_a(lua_State* p_state) {
	lua_pushinteger(p_state, static_cast<lua_Integer>(sf::Keyboard::Key::A));
	return 1;
}
static int key_d(lua_State* p_state) {
	lua_pushinteger(p_state, static_cast<lua_Integer>(sf::Keyboard::Key::D));
	return 1;
}
static int key_w(lua_State* p_state) {
	lua_pushinteger(p_state, static_cast<lua_Integer>(sf::Keyboard::Key::W));
	return 1;
}
static int key_space(lua_State* p_state) {
	lua_pushinteger(p_state, static_cast<lua_Integer>(sf::Keyboard::Key::Space));
	return 1;
}

static int is_key_pressed(lua_State* p_state) {
	const auto key = static_cast<sf::Keyboard::Key>(lua_tointeger(p_state, 1));
	lua_pushboolean(p_state, input::isKeyPressed(key));
	return 1;
}

static constexpr luaL_Reg input[] = {
	{"Key_A",key_a},
	{"Key_D",key_d},
	{"Key_W",key_w},
	{"Key_Space",key_space},
	{"IsKeyPressed",is_key_pressed},
	{nullptr, nullptr}
};

static int input_lib_require(lua_State *p_state) {
	luaL_newlib(p_state, input);
	return 1;
}

void load_input_system_init(lua_State* p_state)
{
	luaL_requiref(p_state, "Input", input_lib_require, 1);
	lua_pop(p_state, 1);
}
