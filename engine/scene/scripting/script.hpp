//
// Created by elnfach on 18.04.2025.
//

#ifndef SCRIPT_HPP
#define SCRIPT_HPP
#include <cstdint>

#include "lua/lua.hpp"

class scriptss {
public:

	void create();
	void close();

	int do_file(const char* filename);
	int load_file(const char* filename);

	template<class Type>
	void register_constant(Type value, const char* name);

	void array();
	template<class Type>
	void register_constant_array(Type p_value, int32_t index);

	void register_array(char* name);

	int32_t get_argument_count();

	template<class Type>
	Type get_argument(int32_t p_index);
	template<class Type>
	void return_value(Type value);

	lua_State* get_state() { return m_state; }
private:
	lua_State* m_state = nullptr;
};

#endif //SCRIPT_HPP
