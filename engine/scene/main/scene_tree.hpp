//
// Created by elnfach on 18.04.2025.
//

#ifndef SCENE_TREE_HPP
#define SCENE_TREE_HPP
#include <cmath>
#include <map>
#include <memory>

#include "scene.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


namespace spacewar
{
	class scene_tree final {
	public:
		static void initialize(const std::shared_ptr<sf::RenderWindow>& p_window);
		static void finalize();
		~scene_tree() = default;
	private:
		static void start_scene();
	public:
		static void add_scene(const std::string& p_name, const std::shared_ptr<scene>& p_scene);
		static void set_current_scene(const std::string& p_name);
		static scene* get_current_scene();

		static void poll_events();
		static void update_scene(float_t p_dt);
	};
}

#endif //SCENE_TREE_HPP
