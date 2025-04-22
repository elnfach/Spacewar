//
// Created by elnfach on 18.04.2025.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>

#include "scene/main/scene_tree.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace spacewar
{
	class engine {
	public:
		engine();
		~engine() = default;

		bool run() const;
		bool running() const;
	private:
		struct Data {
			bool initialized;
			bool running = true;

			bool is_synced = true;
			float_t frame_limit = 60;

			std::shared_ptr<sf::RenderWindow> window = nullptr;
		} m_data;
	};
}



#endif //ENGINE_HPP
