//
// Created by elnfach on 19.04.2025.
//

#include "script_engine.hpp"

#include <iostream>

#include "library/lua_input_system.hpp"
#include "library/lua_entity_system.hpp"
#include "library/lua_network_system.hpp"
#include "library/lua_scene_system.hpp"
#include "scene/entity/game_object.hpp"

struct script_engine_data
{
	std::unordered_map<spacewar::uuid, std::shared_ptr<spacewar::script>> scripts;
	std::filesystem::path scripts_path;
	spacewar::scene* context = nullptr;
};
static script_engine_data* s_data = nullptr;

bool spacewar::script_engine::exist_file(const std::string& p_name)
{
	return std::filesystem::exists(s_data->scripts_path / p_name);
}

void spacewar::script_engine::create_game_object(const game_object& p_game_object)
{
	if (const auto& [file_name] = p_game_object.getComponent<ScriptComponent>(); exist_file(file_name))
	{
		const auto [ID] = p_game_object.getComponent<IDComponent>();
		const auto instance = std::make_shared<script>(ID);
		instance->load(file_name);
		s_data->scripts[ID] = instance;
	}
}

void spacewar::script_engine::start_game_object(const uuid& p_uuid)
{
	if (s_data->scripts.contains(p_uuid))
	{
		const auto script = s_data->scripts.at(p_uuid);
		script->invoke_start();
	}
}

void spacewar::script_engine::update_game_object(const uuid& p_uuid, const float p_dt)
{
	if (s_data->scripts.contains(p_uuid))
	{
		const auto script = s_data->scripts.at(p_uuid);
		script->invoke_update(p_dt);
	}
}

void spacewar::script_engine::invoke_function(const uuid& p_uuid, const std::string& p_func_name,
	void* p_args)
{
	if (s_data->scripts.contains(p_uuid))
	{
		const auto script = s_data->scripts.at(p_uuid);
		script->invoke_function(p_func_name, p_args);
	}
}

void spacewar::script_engine::set_current_scene(scene* p_context)
{
	if (p_context != nullptr)
		s_data->context = p_context;
}

spacewar::scene* spacewar::script_engine::get_context_scene()
{
	return s_data->context;
}

void spacewar::script_engine::initialize()
{
	s_data = new script_engine_data();
	s_data->scripts_path = std::format("{0}{1}", RESOURCES, "scripts");
}

void spacewar::script_engine::finalize()
{
	s_data->scripts.clear();
	delete s_data;
	s_data = nullptr;
}

spacewar::script::script(const uuid p_uuid) : m_uuid(p_uuid)
{
	create();
}

spacewar::script::~script()
{
	close();
}

void spacewar::script::create()
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
	load_input_system_init(m_state);
	load_entity_system_init(m_state);
	load_scene_system_init(m_state);
	load_network_system_init(m_state);
}

void spacewar::script::close() const
{
	lua_close(m_state);
}

void spacewar::script::load(const std::string& p_name) const
{
	luaL_openlibs(m_state);
	const auto path = std::format("{0}/{1}", s_data->scripts_path.string(), p_name);
	if (luaL_dofile(m_state, path.c_str()))
	{
		return void();
	}
}

void spacewar::script::invoke_start() const
{
	lua_getglobal(m_state, "start");
	lua_pcall(m_state, 0, 0, 0);
}

void spacewar::script::invoke_update(const float p_dt) const
{
	lua_getglobal(m_state, "update");
	lua_pushnumber(m_state, p_dt);
	lua_pcall(m_state, 1, 0, 0);
}

void spacewar::script::invoke_function(const std::string& p_name, void* p_args) const
{
	lua_getglobal(m_state, p_name.c_str());
	lua_pushlightuserdata(m_state, p_args);
	lua_pcall(m_state, 1, 0, 0);
}
