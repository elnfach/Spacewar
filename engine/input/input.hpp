//
// Created by elnfach on 21.04.2025.
//

#ifndef INPUT_HPP
#define INPUT_HPP

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

namespace sf
{
	class RenderWindow;
}

class input {
public:
	input() = delete;
	explicit input(sf::RenderWindow& window)
		: m_window(window)
	{}

	void pause();
	void resume();

	bool isKeyPressed(sf::Keyboard::Key p_key) const;
	bool isMouseButtonPressed(sf::Mouse::Button p_button) const;
private:
	bool m_is_paused = false;
	sf::RenderWindow& m_window;
};

#endif //INPUT_HPP
