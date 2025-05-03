//
// Created by elnfach on 19.04.2025.
//

#ifndef SCRIPT_ENGINE_HPP
#define SCRIPT_ENGINE_HPP
#include <memory>
#include <filesystem>
#include <unordered_map>

#include "../../main/context.hpp"
#include "config/uuid.hpp"

struct lua_State;
namespace spacewar
{
	class IScript
	{
	protected:
		virtual ~IScript() = default;
	public:

		virtual bool load(const std::string_view& p_path) = 0;
		virtual bool call_function(const ::std::string_view& p_func_name, const std::vector<Variant>& params) = 0;
	};

	class scene;
	class entity;
	class script_engine final : public IScriptableContext {
	public:
		script_engine();
	private:
		bool exist_file(const std::string_view& p_name) const;
		bool script_contains(const uuid& p_uuid) const;
		std::shared_ptr<IScript> get_script_by_uuid(const uuid& p_uuid) const;
	public:
		void create_entity(const entity& p_entity) override;
		void invoke_function(const uuid& p_uuid, const std::string_view& p_func_name, const std::vector<Variant>& params) const override ;
	private:
		std::unordered_map<uuid, std::shared_ptr<IScript>> m_scripts;
		std::filesystem::path m_scripts_path;
		std::shared_ptr<scene> m_context;
	};
}

#endif //SCRIPT_ENGINE_HPP
