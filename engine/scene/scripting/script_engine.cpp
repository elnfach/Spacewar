//
// Created by elnfach on 19.04.2025.
//

#include "script_engine.hpp"

#include "lua_script_api.hpp"
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

std::shared_ptr<spacewar::lua_script> spacewar::script_engine::get_script_by_uuid(const uuid& p_uuid) const
{
	return m_scripts.at(p_uuid);
}


void spacewar::script_engine::create_entity(const entity& p_entity)
{
	if (const auto& [file_name] = p_entity.get_component<ScriptComponent>(); exist_file(file_name))
	{
		const auto [ID] = p_entity.get_component<IDComponent>();
		const auto api = std::make_shared<lua_script_api>(p_entity, m_context);
		const auto instance = std::make_shared<lua_script>(api);
		// TODO: Assets resource manager
		const auto path = std::format("{0}/{1}", m_scripts_path.string(), file_name);
		instance->load(path);
		m_scripts[ID] = instance;
	}
}

spacewar::script_engine::script_engine()
{
	m_scripts_path = std::format("{0}{1}", RESOURCES, "scripts");
}
