//
// Created by elnfach on 19.04.2025.
//


#include <fstream>
#include <iostream>

#include "scene_serializer.hpp"
#include "fkYAML/node.hpp"
#include "scene/entity/entity.hpp"

void spacewar::scene_serializer::serialize(const std::string_view& p_file_path)
{

}

bool spacewar::scene_serializer::deserialize(const std::string_view& p_file_path, const std::shared_ptr<scene>& p_scene)
{
	std::ifstream ifs((p_file_path.data()));
	const fkyaml::node data = fkyaml::node::deserialize(ifs);
	if (data["scene_name"].is_null())
	{
		return false;
	}
	auto scene_name = data["scene_name"].get_value<std::string>();
	auto game_objects = data["game_objects"];
	if (!game_objects.is_null())
	{
		for (auto object : game_objects)
		{
			auto uuid = object["uuid"].get_value<uint64_t>();

			entity deserialized_game_object = p_scene->create_entity(uuid);
			if (auto transform_component = object["TransformComponent"]; !transform_component.is_null())
			{
				auto& [translation, rotation, scale] = deserialized_game_object.get_component<TransformComponent>();
				auto temp = transform_component["translation"].get_value<std::vector<float>>();
				translation = sf::Vector2f(temp[0], temp[1]);
				rotation = transform_component["rotation"].get_value<float_t>();
				temp = transform_component["scale"].get_value<std::vector<float>>();
				scale = sf::Vector2f(temp[0], temp[1]);
			}
			if (auto rect_transform_component = object["RectangleTransformComponent"]; !rect_transform_component.is_null())
			{
				auto& [translation, rotation, scale] = deserialized_game_object.add_component<RectangleTransformComponent>();
				auto temp = rect_transform_component["local_translation"].get_value<std::vector<float>>();
				translation = sf::Vector2f(temp[0], temp[1]);
				rotation = rect_transform_component["local_rotation"].get_value<float_t>();
				temp = rect_transform_component["local_scale"].get_value<std::vector<float>>();
				scale = sf::Vector2f(temp[0], temp[1]);
			}
			if (auto camera_component = object["CameraComponent"]; !camera_component.is_null())
			{
				auto& [view] = deserialized_game_object.add_component<CameraComponent>();
			}
			if (auto text_component = object["TextComponent"]; !text_component.is_null())
			{
				auto& [text, size, font ,color] = deserialized_game_object.add_component<TextComponent>();
				text = text_component["text"].get_value<std::string>();
				size = text_component["size"].get_value<int32_t>();
				font = sf::Font(RESOURCES+text_component["font_path"].get_value<std::string>());
				//text_component["color"].get_value<glm::vec4>()
			}
			if (auto sprite_component = object["SpriteComponent"]; !sprite_component.is_null())
			{
				sf::Texture temp;
				if (!temp.loadFromFile(RESOURCES+sprite_component["texture"].get_value<std::string>()))
				{
					return false;
				}

				auto& [texture, max_size, rect] = deserialized_game_object.add_component<SpriteComponent>();
				texture = temp;
				auto map = sprite_component["max_size"].get_value<std::map<std::string, float>>();
				max_size = sf::Vector2f(map["width"], map["height"]);
			}
			if (auto script_component = object["ScriptComponent"]; !script_component.is_null())
			{
				auto& [path] = deserialized_game_object.add_component<ScriptComponent>();
				path = script_component["file_name"].get_value<std::string>();
			}
			if (auto button_component = object["ButtonComponent"]; !button_component.is_null())
			{
				auto& [on_click, enabled, is_visible, size] = deserialized_game_object.add_component<ButtonComponent>();
				auto map = button_component["size"].get_value<std::map<std::string, float>>();
				on_click = button_component["on_click_function_name"].get_value<std::string>();
				enabled = button_component["enabled"].get_value<bool>();
				is_visible = button_component["is_visible_shape"].get_value<bool>();
				size = sf::RectangleShape(sf::Vector2f(map["width"], map["height"]));
			}
			if (auto network_component = object["NetworkComponent"]; !network_component.is_null())
			{
				auto& [create_function, on_client_connect_function_name, on_client_disconnect_function_name] = deserialized_game_object.add_component<NetworkComponent>();
				create_function = network_component["create_function"].get_value<std::string>();
				on_client_connect_function_name = network_component["on_client_connect_function_name"].get_value<std::string>();
				on_client_disconnect_function_name = network_component["on_client_disconnect_function_name"].get_value<std::string>();
			}
		}
	}
	return true;
}