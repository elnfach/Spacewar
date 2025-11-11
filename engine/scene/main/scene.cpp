//
// Created by elnfach on 18.04.2025.
//

#include "scene.hpp"

#include <iostream>

#include "glm/glm.hpp"

#include "scene_tree.hpp"
#include "scene/entity/entity.hpp"
#include "scene/entity/component.hpp"
#include "../../main/context.hpp"

#include "SFML/Window/Mouse.hpp"

template<class ...Component>
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

template<class ...Component>
static void copy_component(spacewar::ComponentGroup<Component...>, entt::registry& dst, entt::registry& src, const std::unordered_map<spacewar::uuid, entt::entity>& enttMap)
{
	copy_component<Component...>(dst, src, enttMap);
}

template<class ...Component>
static void copy_component_if_exists(spacewar::entity p_destination, spacewar::entity p_source)
{
	([&]()
	{
		if (p_source.has_component<Component>())
			p_destination.add_or_replace_component<Component>(p_source.get_component<Component>());
	}(), ...);
}

template<class ...Component>
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
			m_scriptable_context->create_entity(entity);
			m_scriptable_context->invoke_function(entity.uuid(), "start");
		}
	}

	// Networking
	{
		for (const auto view = m_registry.view<IDComponent, NetworkComponent, ScriptComponent>(); const auto e : view)
		{
			auto [id, network, script] = view.get<IDComponent, NetworkComponent, ScriptComponent>(e);
			m_scriptable_context->invoke_function(id.ID, network.create_function);
		}
	}
}

void spacewar::scene::draw(sf::RenderWindow& p_window)
{
	p_window.clear(sf::Color::Black);

	// Camera
	{
		for (const auto view = m_registry.view<TransformComponent, CameraComponent>(); auto entity : view)
		{
			auto [transform, camera] = view.get(entity);
			sf::View viewport = { transform.translation, sf::Vector2f(m_viewport_size) };
			p_window.setView(viewport);
			break;
		}
	}

	// Text
	{
		for (const auto view = m_registry.view<TransformComponent, TextComponent>(); const auto entity : view)
		{
			auto [transform, component] = view.get(entity);
			sf::Text text(component.font, component.text, component.size);
			text.setPosition(transform.translation);
			text.setRotation(sf::radians(transform.rotation));
			text.setScale(transform.scale);
			text.setFillColor(component.color);
			p_window.draw(text);
		}
	}

	// Button
	{
		for (const auto view = m_registry.view<IDComponent, TransformComponent, RectangleTransformComponent, ButtonComponent>(); const auto entity : view)
		{
			auto [ID, transform, rect_transform, component] = view.get(entity);
			component.rect.setPosition(transform.translation + rect_transform.local_translation);
			const auto size = component.rect.getSize();
			component.rect.setOrigin(sf::Vector2f(size.x / 2.f, size.y / 2.f));
			component.rect.setRotation(sf::radians(transform.rotation + rect_transform.local_rotation));
			component.rect.setScale(sf::Vector2f(transform.scale.x * rect_transform.local_scale.x, transform.scale.y * rect_transform.local_scale.y));

			const sf::Vector2f half = component.rect.getSize() / 2.f;
			const sf::Vector2f center = component.rect.getPosition();

			auto start_position = glm::vec2(center.x - half.x, center.y + half.y);
			auto end_position = glm::vec2(center.x + half.x, center.y - half.y);
			auto world_position = p_window.mapPixelToCoords(sf::Mouse::getPosition(p_window));
			auto mouse_position = glm::vec2(world_position.x, world_position.y);
			glm::vec2 min = glm::min(start_position, end_position);
			glm::vec2 max = glm::max(start_position, end_position);

			auto conditions = glm::vec<2, bool>(
				glm::all(glm::greaterThanEqual(mouse_position, min)),
				glm::all(glm::lessThanEqual(mouse_position, max))
			);


			// TODO: Высокая связанность компонентов
			if (glm::all(conditions) && component.enabled && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				m_scriptable_context->invoke_function(ID.ID, component.on_click_function_name);

			if (component.is_visible_shape)
				p_window.draw(component.rect);
		}
	}

	// Sprites
	{
		for (const auto view = m_registry.view<TransformComponent, RectangleTransformComponent, SpriteComponent>(); const auto entity : view)
		{
			auto [transform, rect_transform, component] = view.get(entity);
			component.sprite.setPosition(transform.translation + rect_transform.local_translation);
			sf::Vector2f texture_size = sf::Vector2f(component.texture.getSize());
			const auto size = texture_size.length() > component.max_size.length() ? component.max_size : texture_size;
			component.sprite.setSize(size);
			component.sprite.setOrigin(sf::Vector2f(size.x / 2, size.y / 2));
			component.sprite.setRotation(sf::degrees(transform.rotation + rect_transform.local_rotation));
			component.sprite.setScale(sf::Vector2f(transform.scale.x * rect_transform.local_scale.x, transform.scale.y * rect_transform.local_scale.y));
			component.sprite.setTexture(&component.texture);

			p_window.draw(component.sprite);
		}
	}

	p_window.display();
}

void spacewar::scene::update(const float_t p_dt)
{
	// Scripting
	{
		for (const auto view = m_registry.view<IDComponent, ScriptComponent>(); const auto e : view)
		{
			entity entity = {e, this};
			m_scriptable_context->invoke_function(entity.uuid(), "update", p_dt);
		}
	}

	// Networking
	{
		for (const auto view = m_registry.view<IDComponent, NetworkComponent, ScriptComponent>(); const auto e : view)
		{
			auto [id, network, script] = view.get(e);
			//m_scriptable_context->invoke_function(id.ID, "SendPosition");
		}
	}
}

spacewar::entity spacewar::scene::create_entity(const uuid p_uuid)
{
	const entity entity = {m_registry.create(), this};
	entity.add_component<IDComponent>(p_uuid);
	entity.add_component<TransformComponent>();
	//m_entities[p_uuid] = entity;
	return entity;
}

spacewar::entity spacewar::scene::copy_entity(const entity& p_entity)
{
	const entity new_entity = create_entity(uuid());
	copy_component_if_exists(AllComponents{}, new_entity, p_entity);
	return new_entity;
}

void spacewar::scene::destroy_entity(const entity& p_game_object)
{
	//m_entities.erase(p_game_object.uuid());
	m_registry.destroy(p_game_object);
}

spacewar::entity spacewar::scene::get_entity_by_uuid(const uuid& uuid) const
{
	/*if (m_entities.contains(uuid))
		return m_entities.at(uuid);*/
	return {};
}

void spacewar::scene::destroy_entity_by_uuid(const uuid& p_uuid)
{
	/*if (m_entities.contains(p_uuid))
		destroy_entity(m_entities.at(p_uuid));*/
}

void spacewar::scene::on_runtime_start()
{
	start();
}

void spacewar::scene::on_runtime_stop()
{
}

void spacewar::scene::set_context(const std::shared_ptr<script_engine>& p_context)
{
	m_scriptable_context = p_context;
}

void spacewar::scene::set_scene_by_name(const std::string_view& p_scene_name)
{
	m_events.push(std::pair(SceneEventSType::CHANGE_SCENE, p_scene_name));
}

bool spacewar::scene::key_is_pressed(const sf::Keyboard::Key& p_key)
{
	m_events.push(std::pair(SceneEventSType::IS_KEY_PRESSED, (char*)p_key));
}

void spacewar::scene::on_update(const float dt, sf::RenderWindow& p_window)
{
	update(dt);
	draw(p_window);
}

void spacewar::scene::viewport_resize(const sf::Vector2u p_viewport)
{
	if (m_viewport_size == p_viewport)
		return;
	m_viewport_size = p_viewport;
	for (const auto view = m_registry.view<CameraComponent>(); const auto entity : view)
	{
		auto& [viewport] = view.get<CameraComponent>(entity);
		viewport.setSize(sf::Vector2f(p_viewport));
	}
}

sf::Vector2u spacewar::scene::get_viewport_size() const
{
	return m_viewport_size;
}

template <typename Type>
	void spacewar::scene::component_added(const entity& p_entity, Type& p_component)
{
	static_assert(sizeof(Type) == 0);
}

template<>
void spacewar::scene::component_added<spacewar::IDComponent>(const entity& entity, IDComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::TransformComponent>(const entity& entity, TransformComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::SpriteComponent>(const entity& entity, SpriteComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::ScriptComponent>(const entity& entity, ScriptComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::TextComponent>(const entity& entity, TextComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::RectangleTransformComponent>(const entity& entity, RectangleTransformComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::ButtonComponent>(const entity& entity, ButtonComponent& component)
{
}

template<>
void spacewar::scene::component_added<spacewar::CameraComponent>(const entity& p_entity, CameraComponent& p_component)
{
	if (m_viewport_size.x > 0 && m_viewport_size.y > 0)
		p_component.view.setSize(sf::Vector2f(m_viewport_size));
}

template<>
void spacewar::scene::component_added<spacewar::NetworkComponent>(const entity& entity, NetworkComponent& component)
{
}