//
// Created by elnfach on 02.05.2025.
//

#include "lua_script.hpp"

#include <cmath>
#include <fstream>
#include <span>

#include "scene/scripting/lua_script_api.hpp"

spacewar::lua_script::lua_script(const std::shared_ptr<lua_script_api>& p_api): m_state(std::move(p_api->get_state()))
{
}

bool spacewar::lua_script::load(const std::string_view& p_path)
{
	std::ifstream file(p_path.data());
	if (!file) {
		std::cerr << "Failed to open script: " << p_path << "\n";
		return false;
	}
	const std::string script((std::istreambuf_iterator<char>(file)),
					   std::istreambuf_iterator<char>());

	sol::load_result script_result = m_state.load(script);
	if (!script_result.valid()) {
		const sol::error err = script_result;
		std::cerr << "Script load failed: " << err.what() << std::endl;
		return false;
	}
	script_result();
	return true;
}