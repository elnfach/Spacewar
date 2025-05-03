//
// Created by elnfach on 18.04.2025.
//

#include "main.hpp"

#include <boost-ext/di.hpp>

#include "config/engine.hpp"
#include "scene/main/scene.hpp"
#include "scene/main/scene_tree.hpp"
#include "scene/networking/network_engine.hpp"
#include "scene/scripting/script_engine.hpp"
#include "scene/serializer/scene_serializer.hpp"

#define nameof(name) #name

bool spacewar::main::init()
{
	auto window = sf::RenderWindow(sf::VideoMode({1080, 720}), "Space war");
	input input_system(window);
	const auto script_engine = std::make_shared<class script_engine>();
	scene_tree scene_tree(window, script_engine);
	const auto injector = boost::di::make_injector(
		boost::di::bind<sf::RenderWindow>().to(window),
		boost::di::bind<class scene_tree>.to(scene_tree),
		boost::di::bind<input>().to(input_system)
	);
	const auto instance = injector.create<engine>();

	// \/ HARDCODING \/
	const auto main_menu = std::make_shared<scene>();
	const auto multiplayer_menu = std::make_shared<scene>();
	const auto game = std::make_shared<scene>();
	// /\ HARDCODING /\

	auto serializer = scene_serializer();
	serializer.deserialize(RESOURCES"scenes/main_menu.yaml", main_menu);
	serializer.deserialize(RESOURCES"scenes/multiplayer.yaml", multiplayer_menu);
	serializer.deserialize(RESOURCES"scenes/game.yaml", game);

	scene_tree.add_scene("MainMenu", main_menu);
	scene_tree.add_scene("MultiplayerMenu", multiplayer_menu);
	scene_tree.add_scene("Game", game);
	scene_tree.set_current_scene("MainMenu");

	if (instance.run()) {
		return false;
	}
	return true;
}
