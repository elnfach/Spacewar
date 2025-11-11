//
// Created by elnfach on 18.04.2025.
//

#ifndef SCENE_HPP
#define SCENE_HPP
#include <queue>
#include <unordered_map>

#include "entt/entt.hpp"
#include "config/uuid.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace spacewar
{
	class script_engine;
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
		enum class SceneEventSType
		{
			SHUTDOWN,
			CHANGE_SCENE,
			IS_KEY_PRESSED,
		};

		std::queue<std::pair<SceneEventSType, std::string_view>>& poll_events() { return m_events; }

		entity create_entity(uuid p_uuid);
		entity copy_entity(const entity& p_entity);
		entity get_entity_by_uuid(const uuid& p_uuid) const;

		void destroy_entity_by_uuid(const uuid& p_uuid);
		void destroy_entity(const entity& p_entity);

		void on_runtime_start();
		void on_runtime_stop();

		void set_context(const std::shared_ptr<script_engine>& p_context);
		void set_scene_by_name(const std::string_view& p_scene_name);
		bool key_is_pressed(const sf::Keyboard::Key& p_key);

		void on_update(float dt, sf::RenderWindow& p_window);

		void viewport_resize(sf::Vector2u p_viewport);
		[[nodiscard]] sf::Vector2u get_viewport_size() const;
	private:
		entt::registry m_registry;
		//std::unordered_map<uuid, entity> m_entities;
		std::queue<std::pair<SceneEventSType, std::string_view>> m_events;

		sf::Vector2u m_viewport_size;

		std::shared_ptr<script_engine> m_scriptable_context;

		friend class entity;
	};
}

#endif //SCENE_HPP
