//
// Created by elnfach on 18.04.2025.
//

#include "scene.hpp"

#include <iostream>

#include "scene_tree.hpp"
#include "glm/glm.hpp"

#include "SFML/Window/Mouse.hpp"
#include "scene/entity/entity.hpp"
#include "scene/entity/game_object.hpp"
#include "scene/entity/component.hpp"
#include "scene/networking/network_engine.hpp"

#include "scene/scripting/script_engine.hpp"

template<typename... Component>
	static void copy_component(entt::registry& dst, entt::registry& src, const std::unordered_map<spacewar::uuid, entt::entity>& enttMap)
{
	([&]()
	{
		for (auto view = src.view<Component>(); auto srcEntity : view)
		{
			entt::entity dstEntity = enttMap.at(src.get<spacewar::IDComponent>(srcEntity).ID);
			auto& srcComponent = src.get<Component>(srcEntity);
			dst.emplace_or_replace<Component>(dstEntity, srcComponent);
		}
	}(), ...);
}

template<typename... Component>
static void copy_component(spacewar::ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<spacewar::uuid, entt::entity>& enttMap)
{
	copy_component<Component...>(dst, src, enttMap);
}

template<typename... Component>
static void copy_component_if_exists(spacewar::entity p_destination, spacewar::entity p_source)
{
	([&]()
	{
		if (p_source.has_component<Component>())
			p_destination.add_or_replace_component<Component>(p_source.get_component<Component>());
	}(), ...);
}

template<typename... Component>
static void copy_component_if_exists(spacewar::ComponentGroup<Component...>, const spacewar::entity p_destination, const spacewar::entity p_source)
{
	copy_component_if_exists<Component...>(p_destination, p_source);
}

void spacewar::scene::start()
{
	// Scripting
	{
		for (const auto view = m_registry.view<ScriptComponent>(); const auto e : view)
		{
			entity entity = {e, this};
			game_object gm = {entity};
			script_engine::create_game_object(gm);
			script_engine::invoke_function(gm.uuid(), "start");
		}
	}

	// Networking
	{
		for (const auto view = m_registry.view<IDComponent, NetworkComponent, ScriptComponent>(); const auto e : view)
		{
			auto [id, network, script] = view.get<IDComponent, NetworkComponent, ScriptComponent>(e);
			script_engine::invoke_function(id.ID, network.create_function);
		}
	}
}

void spacewar::scene::draw(const std::shared_ptr<sf::RenderWindow>& p_window)
{
	p_window->clear(sf::Color::Black);

	// Text
	{
		for (const auto view = m_registry.view<TransformComponent, TextComponent>(); const auto entity : view)
		{
			auto [transform, component] = view.get<TransformComponent, TextComponent>(entity);
			sf::Text text(component.font, component.text, component.size);
			text.setPosition(transform.translation);
			text.setRotation(sf::radians(transform.rotation));
			text.setScale(transform.scale);
			text.setFillColor(component.color);
			p_window->draw(text);
		}
	}

	// Button
	{
		for (const auto view = m_registry.view<IDComponent, TransformComponent, ButtonComponent>(); const auto entity : view)
		{
			auto [ID, transform, component] = view.get(entity);
			component.rect.setPosition(transform.translation);
			const auto size = component.rect.getSize();
			component.rect.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
			component.rect.setRotation(sf::radians(transform.rotation));
			component.rect.setScale(transform.scale);

			const float half_width = component.rect.getSize().x / 2.f;
			const float half_height = component.rect.getSize().y / 2.f;
			const float center_x = transform.translation.x;
			const float center_y = transform.translation.y;

			auto start_position = glm::vec2(center_x - half_width, center_y + half_height);
			auto end_position = glm::vec2(center_x + half_width, center_y - half_height);
			auto mouse_position = glm::vec2(sf::Mouse::getPosition(*p_window).x,sf::Mouse::getPosition(*p_window).y);
			glm::vec2 min = glm::min(start_position, end_position);
			glm::vec2 max = glm::max(start_position, end_position);

			auto conditions = glm::vec<2, bool>(
				glm::all(glm::greaterThanEqual(mouse_position, min)),
				glm::all(glm::lessThanEqual(mouse_position, max))
			);

			if (glm::all(conditions) && component.enabled && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				script_engine::invoke_function(ID.ID, component.on_click_function_name);
			}

			if (component.is_visible_shape)
				p_window->draw(component.rect);
		}
	}

	// Sprites
	{
		for (const auto view = m_registry.view<TransformComponent, SpriteComponent>(); const auto entity : view)
		{
			auto [transform, component] = view.get<TransformComponent, SpriteComponent>(entity);
			component.sprite.setPosition(sf::Vector2f(transform.translation.x, transform.translation.y) + component.offset);
			sf::Vector2f texture_size = sf::Vector2f(component.texture.getSize());
			const auto size = texture_size.length() > component.max_size.length() ? component.max_size : texture_size;
			component.sprite.setSize(size);
			component.sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
			component.sprite.setRotation(sf::degrees(transform.rotation));
			component.sprite.setScale(transform.scale);
			component.sprite.setTexture(&component.texture);

			p_window->draw(component.sprite);
		}
	}

	p_window->display();
}

void spacewar::scene::update(const float_t p_dt)
{
	// Scripting
	{
		for (const auto view = m_registry.view<IDComponent, ScriptComponent>(); const auto e : view)
		{
			entity entity = {e, this};
			script_engine::invoke_function(entity.uuid(), "update", p_dt);
		}
	}

	// Networking
	{
		for (const auto view = m_registry.view<IDComponent, NetworkComponent, ScriptComponent>(); const auto e : view)
		{
			auto [id, network, script] = view.get<IDComponent, NetworkComponent, ScriptComponent>(e);
			script_engine::invoke_function(id.ID, "SendPosition");
		}
	}
}

spacewar::game_object spacewar::scene::create_entity(const uuid p_uuid)
{
	const entity entity = {m_registry.create(), this};
	game_object game_object = {entity};
	game_object.addComponent<IDComponent>(p_uuid);
	game_object.addComponent<TransformComponent>();
	m_entities[p_uuid] = entity;
	return game_object;
}

spacewar::game_object spacewar::scene::copy_entity(const entity& p_entity)
{
	game_object new_entity = create_entity(uuid());
	copy_component_if_exists(AllComponents{}, new_entity.entity, p_entity);
	return new_entity;
}

void spacewar::scene::destroy_entity(const game_object& p_game_object)
{
	m_entities.erase(p_game_object.uuid());
	m_registry.destroy(p_game_object.entity);
}

spacewar::entity spacewar::scene::get_object_by_uuid(const uuid& uuid) const
{
	if (m_entities.contains(uuid))
		return m_entities.at(uuid);
	return {};
}

void spacewar::scene::destroy_entity_by_uuid(const uuid& p_uuid)
{
	if (m_entities.contains(p_uuid))
		destroy_entity(m_entities.at(p_uuid));
}

void spacewar::scene::on_runtime_start()
{
	start();
	script_engine::set_current_scene(scene_tree::get_current_scene());
}

void spacewar::scene::on_runtime_stop()
{
}

void spacewar::scene::on_update(float dt, const std::shared_ptr<sf::RenderWindow>& p_window)
{
	update(dt);
	draw(p_window);
}