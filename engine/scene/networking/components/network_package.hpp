//
// Created by elnfach on 30.04.2025.
//

#ifndef NETWORK_PACKAGE_HPP
#define NETWORK_PACKAGE_HPP
#include <cstdint>
#include <vector>


class network_package {
public:
	network_package() = default;
	~network_package() = default;
private:
public:

	void clear();


	template<class Type>
	network_package& operator<<(Type value) noexcept;
	template<class Type>
	network_package& operator>>(Type value) noexcept;
private:
	std::pmr::vector<int8_t> m_data;
	size_t m_read_size;
	bool m_is_valid;
};
#endif //NETWORK_PACKAGE_HPP
