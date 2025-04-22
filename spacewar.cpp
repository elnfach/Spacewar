#include <iostream>

#include "config/engine.hpp"
#include "main/main.hpp"
#include "scene/scripting/script.hpp"

#include "lua/lua.hpp"

#define nameof(name) #name

/*script script;

// Функция Write для текста
int Write(lua_State*)
{
	for(int i = 1; i < script.get_argument_count()+1; i++)
		std::cout << script.get_argument<char*>(i);
	return 0;
}*/

int main()
{
	/*script.create();
	script.register_constant<lua_CFunction>(Write,"Write");
	script.do_file(RESOURCES"scripts/player.lua");
	system("pause");
	script.close();*/

	if (spacewar::main main; main.init()) {
		return EXIT_FAILURE;
	}
	return 0;
}
