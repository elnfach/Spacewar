//
// Created by elnfach on 02.05.2025.
//

#ifndef LUA_SCRIPT_HPP
#define LUA_SCRIPT_HPP
#include <variant>
#include <vector>

#include "scene/scripting/script_engine.hpp"
#include "sol/state.hpp"

namespace spacewar
{
	class lua_script_api;
}

namespace spacewar
{
	class lua_script final
	{
	public:
		explicit lua_script(const std::shared_ptr<lua_script_api>& p_api);
	public:
		bool load(const std::string_view& p_path);

		template<class ...Args>
		bool call_function(const std::string_view& p_func_name, Args& ...p_args)
		{
			const sol::function func = m_state[p_func_name.data()];
			if (!func.valid()) {
				return false;
			}
			func(std::forward<Args>(p_args)...);
			return true;
		}
	private:
		sol::state m_state;
	};
}

#endif //LUA_SCRIPT_HPP
