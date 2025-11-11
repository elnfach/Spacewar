//
// Created by elnfach on 05.05.2025.
//

#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include <memory>
#include <unordered_map>
#include <typeindex>

class ISubsystem
{
protected:
	virtual ~ISubsystem() = default;
};

class application {
public:
	static application& instance();

private:
	application() = default;
	~application() = default;
public:
	template<class TSubsystem> requires std::is_base_of_v<ISubsystem, TSubsystem>
	void insert(const std::shared_ptr<TSubsystem>& p_subsystem)
	{
		const auto key = std::type_index(typeid(TSubsystem));
		m_subsystems[key](p_subsystem);
	}

	template<class TSubsystem> requires std::is_base_of_v<ISubsystem, TSubsystem>
	std::shared_ptr<TSubsystem> get()
	{
		const auto key = std::type_index(typeid(TSubsystem));
		if (const auto subsystem = m_subsystems[key])
		{
			return std::static_pointer_cast<TSubsystem>(subsystem);
		}
		return nullptr;
	}
private:
	std::pmr::unordered_map<std::type_index, std::shared_ptr<ISubsystem>> m_subsystems;
};

#endif //APPLICATION_HPP
