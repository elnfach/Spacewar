//
// Created by elnfach on 21.04.2025.
//

#ifndef INPUT_HPP
#define INPUT_HPP
#include <memory>

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

namespace sf
{
	class RenderWindow;
}

class input {
public:
	static void initialize(const std::shared_ptr<sf::RenderWindow>& p_window);
	static void finalize();

	static void pause();
	static void resume();

	static bool isKeyPressed(sf::Keyboard::Key p_key);
	static bool isMouseButtonPressed(sf::Mouse::Button p_button);
};



#endif //INPUT_HPP
