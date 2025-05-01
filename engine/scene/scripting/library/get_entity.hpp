//
// Created by elnfach on 20.04.2025.
//

#ifndef GET_ENTITY_HPP
#define GET_ENTITY_HPP

#include "lua/lua.hpp"
#include "scene/scripting/script_engine.hpp"


inline std::optional<spacewar::entity> get_entity(lua_State* p_state, const int p_id) {
	const auto id = lua_tointeger(p_state, p_id);
	const auto scene = spacewar::script_engine::get_context_scene();
	return scene->get_entity_by_uuid(id);
}

#endif //GET_ENTITY_HPP
