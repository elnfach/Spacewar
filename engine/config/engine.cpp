//
// Created by elnfach on 18.04.2025.
//

#include "engine.hpp"

#include <iostream>
#include <thread>

#include "scene/main/scene_tree.hpp"
#include "scene/scripting/script_engine.hpp"
#include "scene/serializer/scene_serializer.hpp"
#include "SFML/Graphics.hpp"

bool spacewar::engine::run() const
{
	m_window.setVerticalSyncEnabled(m_is_synced);
	m_window.setFramerateLimit(m_frame_limit);
	sf::Clock clock;
	float_t elapsed = 0.f;
	float_t frame_time = 0.f;
	while (m_window.isOpen()) {
		m_scene_tree.poll_events();
		m_scene_tree.get_current_scene()->viewport_resize(m_window.getSize());
		while (const std::optional event = m_window.pollEvent()) {
			if (event->is<sf::Event::FocusLost>()) m_input.pause();
			if (event->is<sf::Event::FocusGained>()) m_input.resume();
			if (event->is<sf::Event::Closed>()) m_window.close();
		}
		elapsed = clock.restart().asSeconds();
		frame_time += elapsed;
		if (frame_time>=1.f / m_frame_limit)
		{
			m_scene_tree.update_scene(frame_time);
			frame_time = 0.f;
		}
	}
	return true;
}

bool spacewar::engine::is_running() const
{
	return m_window.isOpen();
}

void spacewar::engine::shutdown() const
{
	m_window.close();
}
