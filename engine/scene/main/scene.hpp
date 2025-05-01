//
// Created by elnfach on 18.04.2025.
//

#ifndef SCENE_HPP
#define SCENE_HPP
#include <cmath>
#include <memory>
#include <unordered_map>

#include "entt/entt.hpp"
#include "config/uuid.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace spacewar
{
	class entity;
	class scene final {
	public:
		scene() = default;
		~scene() = default;

	private:
		void start();

		void draw(sf::RenderWindow& p_window);
		void update(float_t p_dt);

		template<typename Type>
		void component_added(const entity& p_entity, Type& p_component);
	public:

		entity create_entity(uuid p_uuid);
		entity copy_entity(const entity& p_entity);
		entity get_entity_by_uuid(const uuid& p_uuid) const;

		void destroy_entity_by_uuid(const uuid& p_uuid);
		void destroy_entity(const entity& p_entity);

		void on_runtime_start();
		void on_runtime_stop();

		void on_update(float dt, sf::RenderWindow& p_window);

		void viewport_resize(sf::Vector2u p_viewport);
		sf::Vector2u get_viewport_size() const;
	private:
		entt::registry m_registry;
		std::unordered_map<uuid, entity> m_entities;

		sf::Vector2u m_viewport_size;

		friend class entity;
	};
}

#endif //SCENE_HPP
