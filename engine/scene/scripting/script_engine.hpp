//
// Created by elnfach on 19.04.2025.
//

#ifndef SCRIPT_ENGINE_HPP
#define SCRIPT_ENGINE_HPP
#include <sys/stat.h>

#include "script.hpp"
#include "scene/entity/game_object.hpp"

namespace spacewar
{
	class script
	{
	public:
		script(uuid p_uuid);
		~script();
	private:
		void create();
		void close() const;
	public:

		void load(const std::string& p_name) const;

		void invoke_start() const;
		void invoke_update(float p_dt) const;
		void invoke_function(const std::string& p_name, void* p_args) const;
	private:
		uuid m_uuid;
		lua_State* m_state = nullptr;
	};

	class script_engine final {
	public:
		static void initialize();
		static void finalize();
	private:
		static bool exist_file(const std::string& p_name);
	public:
		static void create_game_object(const game_object& p_game_object);
		static void start_game_object(const uuid& p_uuid);
		static void update_game_object(const uuid& p_uuid, float p_dt);
		static void invoke_function(const uuid& p_uuidt, const std::string& p_func_name, void* p_args);
		//static void invoke_listen_function(const uuid& p_uuidt, );

		static void set_current_scene(scene* p_context);
		static scene* get_context_scene();

	private:
		/*static struct Data
		{
			bool initialized = false;
			script instance;
			spacewar::game_object* game_object = nullptr;
		} m_data;*/
	};
}



#endif //SCRIPT_ENGINE_HPP
