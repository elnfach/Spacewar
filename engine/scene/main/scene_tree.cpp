//
// Created by elnfach on 18.04.2025.
//

#include "scene_tree.hpp"

void spacewar::scene_tree::add_scene(const std::string& p_name, const std::shared_ptr<scene>& p_scene) {
	if (!m_scenes.contains(p_name))
	{
		m_scenes.insert({p_name, p_scene});
		if (!m_current_scene_node)
			m_current_scene_node = p_scene;
	}
}

void spacewar::scene_tree::set_current_scene(const std::string& p_name) {
	if (m_scenes.contains(p_name)) {
		m_scene_name = p_name;
		m_needs_to_update = true;
	}
}

spacewar::scene* spacewar::scene_tree::get_current_scene() const {
	return m_current_scene_node.get();
}

void spacewar::scene_tree::poll_events() {
	if (m_needs_to_update) {
		m_current_scene_node = m_scenes[m_scene_name.data()];
		m_needs_to_update = false;
		start_scene();
	}
}

void spacewar::scene_tree::start_scene() const {
	m_current_scene_node->on_runtime_start();
}

void spacewar::scene_tree::update_scene(const float_t p_dt) const {
	m_current_scene_node->on_update(p_dt, m_window);
}
