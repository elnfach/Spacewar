//
// Created by elnfach on 04.05.2025.
//

#ifndef SCRIPT_API_HPP
#define SCRIPT_API_HPP
#include <memory>

#include "main/context.hpp"
#include "scene/entity/component.hpp"
#include "sol/sol.hpp"

namespace spacewar
{
	class scene;
	class entity;
	class component_registrator;
	class lua_script_api final : public IScriptableAPIContext, public ILuaScriptableStateAPIContext {
	public:
		explicit lua_script_api(const entity& p_entity, const std::shared_ptr<scene>& p_context);
		~lua_script_api() override = default;
	private:
		template<class Component>
		void register_component();

		template<class Type>
		void register_types();

		template<typename... Components>
		void register_components(ComponentGroup<Components...>) {
			([&]() {
				register_component<Components>();
			}(), ...);
		}
	public:
		void register_components() override;
		void register_functions() override;
		void register_types() override;
		sol::state& get_state() override;

	private:
		sol::state m_state;
		const entity& entity;
		std::shared_ptr<scene> m_context;
	};
}

#endif //SCRIPT_API_HPP
