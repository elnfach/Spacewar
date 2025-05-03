//
// Created by elnfach on 19.04.2025.
//

#include "script_engine.hpp"

#include "lua/lua_script.hpp"
#include "scene/entity/entity.hpp"

bool spacewar::script_engine::exist_file(const std::string_view& p_name) const
{
	return std::filesystem::exists(m_scripts_path / p_name);
}

bool spacewar::script_engine::script_contains(const uuid& p_uuid) const
{
	return m_scripts.contains(p_uuid);
}

std::shared_ptr<spacewar::IScript> spacewar::script_engine::get_script_by_uuid(const uuid& p_uuid) const
{
	return m_scripts.at(p_uuid);
}

void spacewar::script_engine::create_entity(const entity& p_entity)
{
	if (const auto& [file_name] = p_entity.get_component<ScriptComponent>(); exist_file(file_name))
	{
		const auto [ID] = p_entity.get_component<IDComponent>();
		const auto instance = std::make_shared<lua_script>();
		// TODO: Assets resource manager
		const auto path = std::format("{0}/{1}", m_scripts_path.string(), file_name);
		instance->load(path);
		m_scripts[ID] = instance;
	}
}

void spacewar::script_engine::invoke_function(
	const uuid& p_uuid,
	const std::string_view& p_func_name,
	const std::vector<Variant>& params
) const {
	if (script_contains(p_uuid))
	{
		const auto script = get_script_by_uuid(p_uuid);
		script->call_function(p_func_name.data(), params);
	}
}

spacewar::script_engine::script_engine()
{
	m_scripts_path = std::format("{0}{1}", RESOURCES, "scripts");
}
