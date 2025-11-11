//
// Created by elnfach on 04.05.2025.
//

#include "lua_script_api.hpp"


#include "input/input.hpp"
#include "sol/sol.hpp"
#include "scene/entity/component.hpp"
#include "scene/entity/entity.hpp"
#include "scene/main/scene_tree.hpp"
#include "scene/networking/network_engine.hpp"

spacewar::lua_script_api::lua_script_api(const spacewar::entity& p_entity, const std::shared_ptr<scene>& p_context)
	: entity(p_entity), m_context(p_context)
{
	m_state.open_libraries(sol::lib::base, sol::lib::table, sol::lib::math, sol::lib::io, sol::lib::string);
	register_types();
	register_components();
	register_functions();
}

template<>
void  spacewar::lua_script_api::register_component<spacewar::TransformComponent>()
{
	auto& component = entity.get_component<TransformComponent>();
	m_state.new_usertype<TransformComponent>("Transform",
		"position", &TransformComponent::translation,
		"rotation", &TransformComponent::rotation,
		"scale", &TransformComponent::scale,
		"SetPosition", &TransformComponent::set_position,
		"SetRotation", &TransformComponent::set_rotation
	);
	m_state["transform"] = &component;
}

template<>
void  spacewar::lua_script_api::register_component<spacewar::SpriteComponent>()
{

}

template<>
void  spacewar::lua_script_api::register_component<spacewar::CameraComponent>()
{

}

template<>
void  spacewar::lua_script_api::register_component<spacewar::RectangleTransformComponent>()
{

}

template<>
void  spacewar::lua_script_api::register_component<spacewar::TextComponent>()
{

}

template<>
void  spacewar::lua_script_api::register_component<spacewar::ButtonComponent>()
{

}

template<>
void  spacewar::lua_script_api::register_component<spacewar::ScriptComponent>()
{

}

template<>
void  spacewar::lua_script_api::register_component<spacewar::scene>()
{
	m_state.new_usertype<scene>("Scene",
		"SetScene", &scene::set_scene_by_name
	);
	const auto& context = m_context;
	m_state["scene"] = context.get();
}

template<>
void  spacewar::lua_script_api::register_component<input>() {
	/*m_state.new_usertype<input>("Input",
	"IsKeyPressed", &scene::copy_entity,
	"key.a", sf::Keyboard::Key::A,
	"key.w", sf::Keyboard::Key::W,
	"key.d", sf::Keyboard::Key::D,
	"key.space", sf::Keyboard::Key::Space
	);
	const auto& context = new input(a);
	m_state["input"] = context;*/
}

template<>
void  spacewar::lua_script_api::register_component<spacewar::network_engine>() {
	m_state.new_usertype<network_engine>("NetworkEngine",
		"StartServer", &network_engine::start_server,
		"Connect", &network_engine::start_client,
		"Send", &network_engine::client_send_data
	);
	m_state["network"] = network_engine::get_instance();
}

void spacewar::lua_script_api::register_components()
{
	register_components(AllComponents{});
	register_component<scene>();
	register_component<input>();
	register_component<network_engine>();
}

void spacewar::lua_script_api::register_functions() {

}

template<>
void spacewar::lua_script_api::register_types<sf::Vector2f>()
{
	m_state.new_usertype<sf::Vector2f>("Vector2f",
	                                   "x", &sf::Vector2f::x,
	                                   "y", &sf::Vector2f::y);
}

void spacewar::lua_script_api::register_types()
{
	register_types<sf::Vector2f>();
}

sol::state& spacewar::lua_script_api::get_state()
{
	return m_state;
}
