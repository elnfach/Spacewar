//
// Created by elnfach on 02.05.2025.
//

#include "lua_script.hpp"

#include <cmath>

#include "scene/scripting/library/lua_util.hpp"

spacewar::lua_script::lua_script()
{
	m_state = luaL_newstate();
	if (m_state == nullptr) {
		printf("Failed to create Lua state\n");
		return;
	}
	static constexpr luaL_Reg lua_libs[] = {
		{ "base", luaopen_base },
		{ "io", luaopen_io },
		{ nullptr, nullptr }
	};

	for (const luaL_Reg *lib = lua_libs; lib->func != nullptr; lib++)
	{
		luaL_requiref(m_state, lib->name, lib->func, 1);
		lua_settop(m_state, 0);
	}
	/*load_input_system(m_state);
	load_entity_system(m_state);
	load_scene_system(m_state);
	load_network_system(m_state);
	lua_screen_system(m_state);
	lua_application_system(m_state);*/
}

spacewar::lua_script::~lua_script()
{
	lua_close(m_state);
}

template <>
void spacewar::lua_script::push_value<int32_t>(const int32_t p_value)
{
	lua_pushinteger(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<int64_t>(const int64_t p_value)
{
	lua_pushinteger(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<uint64_t>(const uint64_t p_value)
{
	lua_pushinteger(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<float_t>(const float_t p_value)
{
	lua_pushnumber(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<double_t>(const double_t p_value)
{
	lua_pushnumber(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<sf::Vector2f>(const sf::Vector2f p_value)
{
	push_vec2f(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<std::string>(const std::string p_value)
{
	lua_pushstring(m_state, p_value.data());
}

template <>
void spacewar::lua_script::push_value<bool>(const bool p_value)
{
	lua_pushboolean(m_state, p_value);
}

template <>
void spacewar::lua_script::push_value<lua_CFunction>(const lua_CFunction p_value)
{
	lua_pushcfunction(m_state, p_value);
}

bool spacewar::lua_script::load(const std::string_view& p_path)
{
	luaL_openlibs(m_state);
	luaL_dofile(m_state, p_path.data());
	return true;
}

bool spacewar::lua_script::call_function(const std::string_view& p_func_name, const std::vector<Variant>& params)
{
	lua_getglobal(m_state, p_func_name.data());
	for (const auto& param : params)
	{
		std::visit([&](auto&& arg){
			push_value(arg);
		}, param);
	}
	lua_pcall(m_state, params.size(), 0, 0);
	return true;
}