//
// Created by elnfach on 18.04.2025.
//

#ifndef COMPONENT_HPP
#define COMPONENT_HPP
#include <functional>
#include <cmath>
#include "SFML/System.hpp"
#include "config/uuid.hpp"
#include "SFML/Graphics.hpp"

namespace spacewar
{
	struct IDComponent
	{
		uuid ID;
	};

	struct TransformComponent
	{
		sf::Vector2f translation = { 0.f, 0.f };
		float_t rotation = 0.f;
		sf::Vector2f scale = { 1.f, 1.f };
	};

	struct SpriteComponent
	{
		sf::Vector2f offset = { 0.f, 0.f };
		sf::Texture texture;
		sf::Vector2f max_size = { 100.f, 100.f };
		sf::RectangleShape sprite;
	};

	struct CharacterControllerComponent
	{

	};

	struct ScriptComponent
	{
		std::string file_name;
	};

	struct TextComponent
	{
		std::string text;
		uint32_t size = 16;
		sf::Font font;
		sf::Color color = sf::Color::White;
	};

	struct ButtonComponent
	{
		std::string on_click_function_name;
		bool enabled = true;
		bool is_visible_shape = true;
		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(100.f, 25.f));
	};

	struct NetworkComponent
	{
		std::string create_function;
		std::string on_client_connect_function_name;
		std::string on_client_disconnect_function_name;
	};

	template<typename... Component>
	struct ComponentGroup
	{
	};

	using AllComponents = ComponentGroup<TransformComponent, SpriteComponent,
		ScriptComponent, TextComponent, ButtonComponent>;
}

#endif //COMPONENT_HPP