//
// Created by elnfach on 29.04.2025.
//

#ifndef ENGINE_MODULE_HPP
#define ENGINE_MODULE_HPP
#include <boost-ext/di.hpp>
#include "SFML/Graphics.hpp"

#include "config/engine.hpp"

struct singleton : boost::di::scopes::singleton
{

};

static auto window_props_module() noexcept
{
	return boost::di::make_injector(
		boost::di::bind<sf::RenderWindow>()
		.to(sf::RenderWindow(sf::VideoMode({1080, 720}), "Space war"))
	);
}

static auto scene_tree_module() noexcept
{
	return boost::di::make_injector(
		window_props_module()
	);
}

static auto engine_module() noexcept
{
	return boost::di::make_injector(
		window_props_module(),
		scene_tree_module()
	);
}


#endif //ENGINE_MODULE_HPP