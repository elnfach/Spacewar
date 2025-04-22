// //
// // Created by elnfach on 18.04.2025.
// //
//
// #include "script.hpp"
//
// #include <cmath>
// #include <cstdint>
// #include <iostream>
//
// void script::create()
// {
// 	m_state = luaL_newstate();
//
// 	static constexpr luaL_Reg lua_libs[] = {
// 		{ "base", luaopen_base },
// 		{ "io", luaopen_io },
// 		{ nullptr, nullptr }
// 	};
//
// 	for (const luaL_Reg *lib = lua_libs; lib->func != nullptr; lib++)
// 	{
// 		luaL_requiref(m_state, lib->name, lib->func, 1);
// 		lua_settop(m_state, 0);
// 	}
// }
//
// void script::close()
// {
// 	lua_close(m_state);
// }
//
// int script::do_file(const char* filename)
// {
// 	luaL_dofile(m_state, filename);
// 	return lua_tointeger(m_state, lua_gettop(m_state));
// }
//
// int script::load_file(const char* filename)
// {
// 	if (luaL_loadfile(m_state, filename))
// 	{
// 		std::cerr << "Something went wrong loading the chunk (syntax error?)" << std::endl;
// 		std::cerr << lua_tostring(m_state, -1) << std::endl;
// 		lua_pop(m_state, 1);
// 		return 1;
// 	}
// 	return 0;
// }
//
// template <>
// void script::register_constant<int32_t>(int32_t value, const char* name)
// {
// 	lua_pushinteger(m_state, value);
// 	lua_setglobal(m_state, name);
// }
//
// template <>
// void script::register_constant<double_t>(const double_t value, const char* name)
// {
// 	lua_pushnumber(m_state, value);
// 	lua_setglobal(m_state, name);
// }
//
// template <>
// void script::register_constant<char*>(char* value, const char* name)
// {
// 	lua_pushstring(m_state, value);
// 	lua_setglobal(m_state, name);
// }
//
// template <>
// void script::register_constant<bool>(bool value, const char* name)
// {
// 	lua_pushboolean(m_state, value);
// 	lua_setglobal(m_state, name);
// }
//
// template <>
// void script::register_constant<lua_CFunction>(lua_CFunction value, const char* name)
// {
// 	lua_pushcfunction(m_state, value);
// 	lua_setglobal(m_state, name);
// }
//
// void script::array()
// {
// 	lua_createtable(m_state, 2, 0);
// }
//
// void script::register_array(char* name)
// {
// 	lua_setglobal(m_state, name);
// }
//
// int32_t script::get_argument_count()
// {
// 	return lua_gettop(m_state);
// }
//
// template <>
// void script::register_constant_array<int32_t>(const int32_t p_value, const int32_t index)
// {
// 	lua_pushnumber(m_state, index);
// 	lua_pushinteger(m_state, p_value);
// 	lua_settable(m_state, -3);
// }
//
// template <>
// void script::register_constant_array<double_t>(const double_t p_value, const int32_t index)
// {
// 	lua_pushnumber(m_state, index);
// 	lua_pushnumber(m_state, p_value);
// 	lua_settable(m_state, -3);
// }
//
// template <>
// void script::register_constant_array<char*>(char* p_value, const int32_t index)
// {
// 	lua_pushnumber(m_state, index);
// 	lua_pushstring(m_state, p_value);
// 	lua_settable(m_state, -3);
// }
//
// template <>
// void script::register_constant_array<bool>(const bool p_value, const int32_t index)
// {
// 	lua_pushnumber(m_state, index);
// 	lua_pushboolean(m_state, p_value);
// 	lua_settable(m_state, -3);
// }
//
// template <>
// void script::register_constant_array<lua_CFunction>(const lua_CFunction p_value, const int32_t index)
// {
// 	lua_pushnumber(m_state, index);
// 	lua_pushcfunction(m_state, p_value);
// 	lua_settable(m_state, -3);
// }
//
// template <>
// int32_t script::get_argument<int32_t>(const int32_t p_index)
// {
// 	return lua_tointeger(m_state, p_index);
// }
//
// template <>
// double_t script::get_argument<double_t>(const int32_t p_index)
// {
// 	return lua_tonumber(m_state, p_index);
// }
//
// template <>
// char* script::get_argument<char*>(const int32_t p_index)
// {
// 	return const_cast<char*>(lua_tostring(m_state, p_index));
// }
//
// template <>
// bool script::get_argument<bool>(const int32_t p_index)
// {
// 	return lua_toboolean(m_state, p_index);
// }
//
// template <>
// void script::return_value<int32_t>(const int32_t value)
// {
// 	lua_pushinteger(m_state, value);
// }
//
// template <>
// void script::return_value<double_t>(const double_t value)
// {
// 	lua_tonumber(m_state, value);
// }
//
// template <>
// void script::return_value<char*>(char* value)
// {
// 	lua_pushstring(m_state, value);
// }
//
// template <>
// void script::return_value<bool>(const bool value)
// {
// 	lua_pushboolean(m_state, value);
// }
