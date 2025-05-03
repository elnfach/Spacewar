//
// Created by elnfach on 18.04.2025.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <cmath>

#include "input/input.hpp"

namespace sf {
	class RenderWindow;
}
namespace spacewar
{
	class scene_tree;
	class script_engine;
	class engine {
	public:
		engine() = delete;
		explicit engine(
			sf::RenderWindow& p_window,
			scene_tree& p_scene_tree,
			input& p_input)
			: m_window(p_window), m_scene_tree(p_scene_tree), m_input(p_input)
		{}

		[[nodiscard]] bool run() const;
		[[nodiscard]] bool is_running() const;
		void shutdown() const;

	private:
		bool m_is_synced = true;
		float_t m_frame_limit = 60;

		sf::RenderWindow& m_window;
		scene_tree& m_scene_tree;
		input& m_input;
	};
}

#endif //ENGINE_HPP
