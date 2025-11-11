//
// Created by elnfach on 18.04.2025.
//

#ifndef SCENE_TREE_HPP
#define SCENE_TREE_HPP
#include <map>
#include <memory>

#include "scene.hpp"
#include "scene/scripting/script_engine.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace spacewar
{
	class scene_tree {
	public:
		scene_tree() = delete;
		explicit scene_tree(sf::RenderWindow& p_window, const std::shared_ptr<script_engine>& p_script_engine)
			: m_script_engine(p_script_engine), m_window(p_window)
		{}
	private:
		void start_scene() const;
	public:
		void add_scene(const std::string_view& p_name, const std::shared_ptr<scene>& p_scene);
		void set_current_scene(const std::string_view& p_name);
		[[nodiscard]] scene* get_current_scene() const;

		void poll_events();
		void update_scene(float_t p_dt) const;
	private:
		bool m_needs_to_update = false;
		std::string_view m_scene_name;
		std::shared_ptr<scene> m_current_scene_node = nullptr;
		std::shared_ptr<script_engine> m_script_engine = nullptr;
		std::map<std::string_view, std::shared_ptr<scene>> m_scenes;
		sf::RenderWindow& m_window;
	};
}

#endif //SCENE_TREE_HPP
