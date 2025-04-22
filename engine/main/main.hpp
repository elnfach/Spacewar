//
// Created by elnfach on 18.04.2025.
//

#ifndef MAIN_HPP
#define MAIN_HPP
#include <memory>

namespace spacewar
{
	class engine;

	class main {
	public:
		bool init();
	private:
		std::unique_ptr<engine> m_engine;
	};

}
#endif //MAIN_HPP
