//
// Created by elnfach on 04.05.2025.
//

#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include <string_view>
#include <variant>
#include <vector>

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
		virtual void invoke_function(
			const uuid& p_uuid,
			const std::string_view& p_func_name,
			const std::vector<Variant>& params) const
		= 0;
	};
}

#endif //CONTEXT_HPP
