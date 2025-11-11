// //
// // Created by elnfach on 23.04.2025.
// //
//
// #include "lua_application_system.hpp"
//
// #include "get_entity.hpp"
// #include "lua_util.hpp"
// #include "config/engine.hpp"
// #include "scene/main/scene_tree.hpp"
//
// static int quit_from_application(lua_State *p_state) {
// 	//spacewar::engine::shutdown();
// 	return  0;
// }
//
// static constexpr luaL_Reg scene[] = {
// 	{"Quit",quit_from_application},
// 	{nullptr, nullptr}
// };
//
// static int input_lib_require(lua_State* p_state) {
// 	luaL_newlib(p_state, scene);
// 	return 1;
// }
//
// void lua_application_system(lua_State* p_state)
// {
// 	luaL_requiref(p_state, "Application", input_lib_require, 1);
// 	lua_pop(p_state, 1);
// }
