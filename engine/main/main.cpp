//
// Created by elnfach on 18.04.2025.
//

#include "main.hpp"

bool spacewar::main::init()
{
	m_engine = std::make_unique<engine>();
	if (m_engine->run())
	{
	}
	return true;
}
