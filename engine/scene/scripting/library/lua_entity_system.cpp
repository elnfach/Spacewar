/*//
// Created by elnfach on 20.04.2025.
//

#include "lua_entity_system.hpp"

#include <iostream>

#include "get_entity.hpp"
#include "lua_util.hpp"


// TODO: rework
static int lua_get_uuid(lua_State* p_state)
{
	if (const auto entity = get_entity(p_state, 1)) {
		auto& [ID] = entity->get_component<spacewar::IDComponent>();
		lua_pushnumber(p_state, ID);
	}
	return 1;
}

static int lua_get_rotation(lua_State* p_state)
{
	if (const auto entity = get_entity(p_state, 1)) {
		auto& [transition, rotation, scale] = entity->get_component<spacewar::TransformComponent>();
		lua_pushnumber(p_state, rotation);
	}
	return 1;
}

static int get_position(lua_State* p_state)
{
	if (const auto entity = get_entity(p_state, 1)) {
		auto& [position, rotation, scale] = entity->get_component<spacewar::TransformComponent>();
		return push_vec2f(p_state, position);
	}
	return 0;
}

static int lua_rotate(lua_State* p_state) {
	if (const auto entity = get_entity(p_state, 1)) {
		auto& [transition, rotation, scale] = entity->get_component<spacewar::TransformComponent>();
		const float angle = lua_tonumber(p_state, 2);
		rotation += angle;
	}
	return 0;
}

static int lua_move(lua_State* p_state) {
	if (const auto entity = get_entity(p_state, 1)) {
		auto& [transition, rotation, scale] = entity->get_component<spacewar::TransformComponent>();
		const float x = lua_tonumber(p_state, 2);
		const float y = lua_tonumber(p_state, 3);
		transition += sf::Vector2f(x, y);
	}
	return 0;
}

static int destroy(lua_State* p_state)
{
	if (const auto entity = get_entity(p_state, 1)) {
		auto& [ID] = entity->get_component<spacewar::IDComponent>();
		//spacewar::script_engine::get_context_scene()->destroy_entity_by_uuid(ID);
	}
	return 0;
}

static int copy(lua_State* p_state) {
	if (const auto entity = get_entity(p_state, 1); entity.has_value())
	{
		/*const auto new_game_object = spacewar::script_engine::get_context_scene()->copy_entity(entity.value());
		auto& [translation, rotation, scale] = new_game_object.get_component<spacewar::TransformComponent>();
		const auto position = to_vec2f(p_state, 2);
		const float angle = lua_tonumber(p_state, 3);
		translation = position;
		rotation = angle;
		lua_pushinteger(p_state, new_game_object.uuid());#1#
		return 1;
	}
	return 0;
}

static constexpr luaL_Reg entity[] = {
	{"Copy",copy},
	{"Move",lua_move},
	{"Rotate",lua_rotate},
	{"Destroy",destroy},
	{"GetUUID",lua_get_uuid},
	{"GetRotation",lua_get_rotation},
	{"GetPosition",get_position},
	{nullptr, nullptr}
};

static int input_lib_require(lua_State* p_state) {
	luaL_newlib(p_state,entity);
	return 1;
}

void load_entity_system(lua_State* p_state)
{
	luaL_requiref(p_state, "Entity", input_lib_require, 1);
	lua_pop(p_state, 1);
}*/