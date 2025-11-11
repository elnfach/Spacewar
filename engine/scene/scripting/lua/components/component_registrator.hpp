//
// Created by elnfach on 04.05.2025.
//

#ifndef COMPONENT_REGISTRATOR_HPP
#define COMPONENT_REGISTRATOR_HPP

template<class Component>
	class component_registrator final : public spacewar::ILuaComponentRegistrator {
public:
	using get_name_func = const char* (*)();

	explicit component_registrator(get_name_func getName, void(*register_methods)(lua_State*))
		: m_name(getName), m_register_methods(register_methods)
	{}
private:
public:
	void register_in_lua(lua_State* L) const override
	{
		luaL_newmetatable(L, m_name());
		m_register_methods(L);
		lua_pop(L, 1);
	}

private:
	get_name_func m_name;
	void (*m_register_methods)(lua_State*);
};

#endif //COMPONENT_REGISTRATOR_HPP
