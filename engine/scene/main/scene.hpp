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
	class game_object;
	class entity;
	class scene final {
	public:
		scene() = default;
		virtual ~scene() = default;

	private:
		void start();

		void draw(const std::shared_ptr<sf::RenderWindow>& p_window);
		void update(float_t dt);
	public:

		game_object create_entity(uuid uuid);
		game_object copy_entity(const entity& p_entity);
		entity get_object_by_uuid(const uuid& uuid) const;

		void destroy_entity_by_uuid(const uuid& uuid);
		void destroy_entity(const game_object& p_game_object);

		void on_runtime_start();
		void on_runtime_stop();

		void on_update(float dt, const std::shared_ptr<sf::RenderWindow>& p_window);
	private:
		entt::registry m_registry;
		std::unordered_map<uuid, entity> m_entities;

		friend class entity;
	};
}

#endif //SCENE_HPP
