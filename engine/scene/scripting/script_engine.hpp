//
// Created by elnfach on 19.04.2025.
//

#ifndef SCRIPT_ENGINE_HPP
#define SCRIPT_ENGINE_HPP
#include <memory>
#include <filesystem>
#include <format>
#include <queue>
#include <unordered_map>

#include "config/uuid.hpp"
#include "lua/lua_script.hpp"
#include "main/context.hpp"

namespace spacewar
{
	struct ScriptComponent;
	class lua_script;
}

namespace spacewar
{
	// TODO
	/*template<class Derived>
	class IScript
	{
	protected:
		virtual ~IScript() = default;
	public:
		bool load(const std::string_view& p_path) {
			return static_cast<const Derived*>(this)->load(p_path);
		}
		template<class ...Args>
		bool call_function(const std::string_view& p_func_name, Args& ...p_args) {
			return static_cast<const Derived*>(this)->call_function(p_func_name, std::forward<Args>(p_args)...);
		}
	};*/

	// TODO: CRTP
	class scene;
	class script_engine final {
	public:
		script_engine();
	private:
		bool exist_file(const std::string_view& p_name) const;
		bool script_contains(const uuid& p_uuid) const;
		std::shared_ptr<lua_script> get_script_by_uuid(const uuid& p_uuid) const;
	public:
		void create_entity(const entity& p_entity);

		template<class ...Args>
		void invoke_function(
			const uuid& p_uuid,
			const std::string_view& p_func_name,
			Args& ...p_args)
		{
			if (script_contains(p_uuid))
			{
				const auto script = get_script_by_uuid(p_uuid);
				script->call_function(p_func_name.data(), std::forward<Args>(p_args)...);
			}
		}

		void set_context(const std::shared_ptr<scene>& p_context) { m_context = p_context; }
	private:
		std::unordered_map<uuid, std::shared_ptr<lua_script>> m_scripts;
		std::filesystem::path m_scripts_path;
		std::shared_ptr<scene> m_context;

		friend class scene_tree;
	};
}

#endif //SCRIPT_ENGINE_HPP
