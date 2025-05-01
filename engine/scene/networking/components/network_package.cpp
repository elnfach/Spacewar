//
// Created by elnfach on 30.04.2025.
//

#include "network_package.hpp"

template <class Type>
network_package& network_package::operator<<(Type value) noexcept
{
	m_data.push_back(value);
	m_read_size = m_data.size();
	return *this;
}

template <class Type>
network_package& network_package::operator>>(Type value) noexcept
{

}

void network_package::clear()
{
	m_data.clear();
	m_read_size = 0;
}
