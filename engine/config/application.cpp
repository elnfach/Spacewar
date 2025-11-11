//
// Created by elnfach on 05.05.2025.
//

#include "application.hpp"

application& application::instance()
{
	static application instance;
	return instance;
}
