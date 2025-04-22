//
// Created by elnfach on 21.04.2025.
//

#include "input.hpp"

#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"

struct input_data
{
	bool is_paused = false;
	std::shared_ptr<sf::RenderWindow> window;
};
static input_data* s_input_data = nullptr;

void input::initialize(const std::shared_ptr<sf::RenderWindow>& p_window)
{
	s_input_data = new input_data;
	s_input_data->window = p_window;
}

void input::finalize()
{
	delete s_input_data;
	s_input_data = nullptr;
}

void input::pause()
{
	s_input_data->is_paused = true;
}

void input::resume()
{
	s_input_data->is_paused = false;
}

bool input::isKeyPressed(const sf::Keyboard::Key p_key)
{
	if (!s_input_data->is_paused && sf::Keyboard::isKeyPressed(p_key))
	{
		std::cerr << "Key pressed: " << static_cast<int>(p_key) << std::endl;
		return sf::Keyboard::isKeyPressed(p_key);
	}
	return false;
}

bool input::isMouseButtonPressed(sf::Mouse::Button p_button)
{
}
