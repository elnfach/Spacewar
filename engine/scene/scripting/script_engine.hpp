//
// Created by elnfach on 19.04.2025.
//

#ifndef SCRIPT_ENGINE_HPP
#define SCRIPT_ENGINE_HPP
#include "scene/entity/entity.hpp"

struct lua_State;
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

		template<class Type>
		void push_value(Type p_value);

		void register_constant(const std::string_view& p_name) const;
		void call_function(size_t p_size) const;
	public:

		void load(const std::string& p_name) const;

		template<class ...Args>
		void invoke_function(const std::string_view& p_func_name, Args... p_args)
		{
			const size_t size = sizeof...(Args);
			register_constant(p_func_name);
			([&] {
				push_value(p_args);
			} (), ...);
			call_function(size);
		}
	private:
		uuid m_uuid;
		lua_State* m_state = nullptr;
	};

	class script_engine final {
	public:
		static void initialize();
		static void finalize();
	private:
		static bool exist_file(const std::string_view& p_name);
		static bool script_contains(const uuid& p_uuid);
		static std::shared_ptr<script> get_script_by_uuid(const uuid& p_uuid);
	public:
		static void create_game_object(const entity& p_game_object);

		template<class ...Args>
		static void invoke_function(const uuid& p_uuid, const std::string_view& p_func_name, Args... p_args)
		{
			if (script_contains(p_uuid))
			{
				const auto script = get_script_by_uuid(p_uuid);
				script->invoke_function(p_func_name.data(), std::forward<Args>(p_args)...);
			}
		}

		static void set_current_scene(scene* p_context);
		static scene* get_context_scene();
	};
}

#endif //SCRIPT_ENGINE_HPP
