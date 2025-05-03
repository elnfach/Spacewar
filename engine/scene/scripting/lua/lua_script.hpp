//
// Created by elnfach on 02.05.2025.
//

#ifndef LUA_SCRIPT_HPP
#define LUA_SCRIPT_HPP
#include <variant>
#include <vector>

#include "scene/scripting/script_engine.hpp"

struct lua_State;
namespace spacewar
{
	class lua_script final : public IScript
	{
	public:
		lua_script();
		~lua_script() override;
	private:
		template<class Type>
		void push_value(Type p_value);
	public:
		bool load(const std::string_view& p_path) override;
		bool call_function(const ::std::string_view& p_func_name, const std::vector<Variant>& params) override;
	private:
		lua_State* m_state = nullptr;
	};
}

#endif //LUA_SCRIPT_HPP
