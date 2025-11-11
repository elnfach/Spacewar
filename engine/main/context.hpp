//
// Created by elnfach on 04.05.2025.
//

#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <string_view>
#include <variant>
#include <vector>

namespace sol
{
	class state;
}

namespace spacewar
{
	class entity;
	class uuid;
	using Variant = std::variant<int, float, double, std::string>;
}

namespace spacewar
{
	class IScriptableContext
	{
	protected:
		virtual ~IScriptableContext() = default;
	public:
		virtual void create_entity(const entity& p_entity) = 0;

		template<class ...Args>
		void invoke_function(
			const uuid& p_uuid,
			const std::string_view& p_func_name,
			Args& ...p_args) {}
	};

	class IScriptableAPIContext
	{
	protected:
		virtual ~IScriptableAPIContext() = default;
	public:
		virtual void register_components() = 0;
		virtual void register_types() = 0;
		virtual void register_functions() = 0;
	};

	class ILuaScriptableStateAPIContext {
	public:
		virtual ~ILuaScriptableStateAPIContext() = default;
	public:
		virtual sol::state& get_state() = 0;
	};
}

#endif //CONTEXT_HPP
