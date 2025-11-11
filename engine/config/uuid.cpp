//
// Created by elnfach on 18.04.2025.
//

#include "uuid.hpp"

#include <random>
#include <bits/uniform_int_dist.h>


static std::random_device s_random_device;
static std::mt19937_64 s_engine(s_random_device());
static std::uniform_int_distribution<uint64_t> s_uniform_distribution;
spacewar::uuid::uuid()
	: m_uuid(s_uniform_distribution(s_engine))
{
}

spacewar::uuid::uuid(const uint64_t p_uuid)
	: m_uuid(p_uuid)
{
}