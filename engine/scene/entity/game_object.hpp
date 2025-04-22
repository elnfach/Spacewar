//
// Created by elnfach on 18.04.2025.
//

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP
#include "entity.hpp"

namespace spacewar
{
	class game_object {
	public:
		virtual ~game_object() = default;

		[[nodiscard]] uuid uuid() const { return entity.uuid(); }

		template<class Type>
		Type& getComponent() const
		{
			return entity.get_component<Type>();
		}
		template<class Type, class... Args>
		Type& addComponent(Args... p_args) const
		{
			return entity.add_component<Type, Args...>(p_args...);
		}
		template<typename Type>
		[[nodiscard]] bool hasComponent() const
		{
			return entity.has_component<Type>();
		}

		template<typename Type>
		void removeComponent() const
		{
			entity.remove_component<Type>();
		}
	private:
		explicit game_object(const entity& p_entity) : entity(p_entity) {};
	protected:
		virtual void start() {}
		virtual void update(float dt) {}
	private:
		entity entity;
		friend class scene;
	};
}

#endif //GAME_OBJECT_HPP
