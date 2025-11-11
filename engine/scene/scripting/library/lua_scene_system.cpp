// //
// // Created by elnfach on 20.04.2025.
// //
//
// #include "lua_scene_system.hpp"
//
// #include <iostream>
//
// #include "get_entity.hpp"
// #include "scene/main/scene_tree.hpp"
// #include "scene/scripting/script_engine.hpp"
//
// int load_scene_by_name(lua_State *p_state) {
// 	const auto scene_name = lua_tostring(p_state, 1);
// 	// Here set new scene by name
// 	return 0;
// }
//
// constexpr luaL_Reg scene[] = {
// 	{"LoadSceneByName",load_scene_by_name},
// 	{nullptr, nullptr}
// };
//
// int input_lib_require(lua_State* p_state) {
// 	luaL_newlib(p_state, scene);
// 	return 1;
// }
//
// void load_scene_system(lua_State* p_state)
// {
// 	luaL_requiref(p_state, "Scene", input_lib_require, 1);
// 	lua_pop(p_state, 1);
// }