//
// Created by elnfach on 19.04.2025.
//

#ifndef SCENE_SERIALIZE_HPP
#define SCENE_SERIALIZE_HPP
#include <memory>

#include "scene/main/scene.hpp"


namespace spacewar
{
	class scene_serializer final {
	public:
		scene_serializer() = default;

		void serialize(const std::string& file_path);
		bool deserialize(const std::string& p_file_path, const std::shared_ptr<scene>& p_scene);
	};
}



#endif //SCENE_SERIALIZE_HPP
