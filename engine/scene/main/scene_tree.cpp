//
// Created by elnfach on 18.04.2025.
//

#include "scene_tree.hpp"

#include <iostream>

struct scene_tree_data
{
	std::string scene_name;
	bool need_to_update = false;
	std::shared_ptr<sf::RenderWindow> m_window;
	std::shared_ptr<spacewar::scene> m_current_scene_node = nullptr;
	std::map<std::string, std::shared_ptr<spacewar::scene>> m_scenes;
};
static scene_tree_data* s_scene_tree_data = nullptr;

void spacewar::scene_tree::initialize(const std::shared_ptr<sf::RenderWindow>& p_window)
{
	s_scene_tree_data = new scene_tree_data();
	s_scene_tree_data->m_window = p_window;
}

void spacewar::scene_tree::finalize()
{
	delete s_scene_tree_data;
	s_scene_tree_data = nullptr;
}

void spacewar::scene_tree::add_scene(const std::string& p_name, const std::shared_ptr<scene>& p_scene)
{
	if (!s_scene_tree_data->m_scenes.contains(p_name))
	{
		s_scene_tree_data->m_scenes.insert({p_name, p_scene});
		if (!s_scene_tree_data->m_current_scene_node)
			s_scene_tree_data->m_current_scene_node = p_scene;
	}
}

void spacewar::scene_tree::set_current_scene(const std::string& p_name)
{
	if (s_scene_tree_data->m_scenes.contains(p_name))
	{
		s_scene_tree_data->scene_name = p_name;
		s_scene_tree_data->need_to_update = true;
	}
}

spacewar::scene* spacewar::scene_tree::get_current_scene()
{
	return s_scene_tree_data->m_current_scene_node.get();
}

void spacewar::scene_tree::poll_events()
{
	if (s_scene_tree_data->need_to_update)
	{
		s_scene_tree_data->m_current_scene_node = s_scene_tree_data->m_scenes[s_scene_tree_data->scene_name];
		s_scene_tree_data->need_to_update = false;
		start_scene();
	}
}

void spacewar::scene_tree::start_scene()
{
	std::cerr << "current scene: " << s_scene_tree_data->scene_name << std::endl;
	s_scene_tree_data->m_current_scene_node->on_runtime_start();
}

void spacewar::scene_tree::update_scene(const float_t p_dt) {
	s_scene_tree_data->m_current_scene_node->on_update(p_dt, s_scene_tree_data->m_window);
}
