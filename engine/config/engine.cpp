//
// Created by elnfach on 18.04.2025.
//

#include "engine.hpp"

#include <iostream>
#include <thread>

#include "input/input.hpp"
#include "scene/entity/game_object.hpp"
#include "scene/networking/network_engine.hpp"
#include "scene/scripting/script_engine.hpp"
#include "scene/serializer/scene_serializer.hpp"
#include "SFML/Graphics.hpp"

spacewar::engine::engine()
{
	m_data.running = false;
	m_data.window = std::make_shared<sf::RenderWindow>(sf::VideoMode({1080, 720}), "Space war");
	scene_tree::initialize(m_data.window);
	m_data.window->setVerticalSyncEnabled(m_data.is_synced);
	m_data.window->setFramerateLimit(m_data.frame_limit);
	m_data.initialized = true;
}

bool spacewar::engine::run() const
{
	if (!m_data.initialized) return false;

	const auto main_menu = std::make_shared<scene>();
	const auto multiplayer_menu = std::make_shared<scene>();
	const auto game = std::make_shared<scene>();
	scene_serializer serializer = scene_serializer();
	serializer.deserialize(RESOURCES"scenes/main_menu.yaml", main_menu);
	serializer.deserialize(RESOURCES"scenes/multiplayer.yaml", multiplayer_menu);
	serializer.deserialize(RESOURCES"scenes/game.yaml", game);

	script_engine::initialize();
	network_engine::initialize();
	input::initialize(m_data.window);

	scene_tree::add_scene("MainMenu", main_menu);
	scene_tree::add_scene("MultiplayerMenu", multiplayer_menu);
	scene_tree::add_scene("Game", game);
	scene_tree::set_current_scene("MainMenu");

	sf::Clock clock;
	float_t elapsed = 0.f;
	float_t frame_time = 0.f;
	while (m_data.window->isOpen()) {
		scene_tree::poll_events();
		while (const std::optional event = m_data.window->pollEvent()) {
			if (event->is<sf::Event::FocusLost>()) input::pause();
			if (event->is<sf::Event::FocusGained>()) input::resume();
			if (event->is<sf::Event::Closed>()) m_data.window->close();
			if (event->is<sf::Event::Resized>())
			{
				sf::FloatRect view{sf::Vector2f(0,0), sf::Vector2f(m_data.window->getSize().x, m_data.window->getSize().y)};
				m_data.window->setView(sf::View(view));
			}
		}
		elapsed = clock.restart().asSeconds();
		frame_time += elapsed;
		if (frame_time>=1.f / m_data.frame_limit)
		{
			scene_tree::update_scene(frame_time);
			frame_time = 0.f;
		}
	}
	script_engine::finalize();
	network_engine::finalize();
	input::finalize();
	return true;
}

bool spacewar::engine::running() const
{
	return m_data.running;
}
