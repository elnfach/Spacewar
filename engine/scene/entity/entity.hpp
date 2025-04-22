//
// Created by elnfach on 18.04.2025.
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "component.hpp"
#include "config/uuid.hpp"
#include "scene/main/scene.hpp"

namespace spacewar
{
	class entity {
	public:
		entity() = default;
		entity(const entt::entity& p_entity, scene* p_scene);
		~entity() = default;

		operator bool() const { return m_entity != entt::null; }
		operator entt::entity() const { return m_entity; }
		operator uint32_t() const { return static_cast<uint32_t>(m_entity); }

		[[nodiscard]] uuid uuid() const { return get_component<IDComponent>().ID; }

		bool operator==(const entity& p_other) const
		{
			return m_entity == p_other.m_entity && m_scene == p_other.m_scene;
		}

		bool operator!=(const entity& p_other) const
		{
			return !(*this == p_other);
		}

		template<class Type, class... Args>
		Type& add_component(Args&... p_args) const
		{
			return m_scene->m_registry.emplace<Type>(m_entity, std::forward<Args>(p_args)...);
		}
		template<typename T, typename... Args>
		T& add_or_replace_component(Args&&... args) const
		{
			return m_scene->m_registry.emplace_or_replace<T>(m_entity, std::forward<Args>(args)...);
		}
		template<typename Type>
		[[nodiscard]] Type& get_component() const
		{
			return m_scene->m_registry.get<Type>(m_entity);
		}

		template<typename Type>
		[[nodiscard]] bool has_component() const
		{
			return m_scene->m_registry.all_of<Type>(m_entity);
		}

		template<typename T>
		void remove_component() const
		{
			m_scene->m_registry.remove<T>(m_entity);
		}

	private:
		entt::entity m_entity = entt::null;
		scene* m_scene = nullptr;
	};
}

#endif //ENTITY_HPP
