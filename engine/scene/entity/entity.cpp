//
// Created by elnfach on 18.04.2025.
//

#include "entity.hpp"

spacewar::entity::entity(const entt::entity& p_entity, spacewar::scene* p_scene)
	: m_entity(p_entity), m_scene(p_scene)
{
}
