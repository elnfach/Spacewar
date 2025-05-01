//
// Created by elnfach on 21.04.2025.
//

#include "input.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

void input::pause() {
	m_is_paused = true;
}

void input::resume() {
	m_is_paused = false;
}

bool input::isKeyPressed(const sf::Keyboard::Key p_key) const {
	return (!m_is_paused) ? sf::Keyboard::isKeyPressed(p_key) : false;
}

bool input::isMouseButtonPressed(const sf::Mouse::Button p_button) const {
	return (!m_is_paused) ? sf::Mouse::isButtonPressed(p_button) : false;
}
