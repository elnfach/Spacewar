//
// Created by elnfach on 18.04.2025.
//

#ifndef UUID_HPP
#define UUID_HPP
#include <cstdint>

namespace spacewar
{
	class uuid
	{
	public:
		uuid();
		uuid(uint64_t p_uuid);
		uuid(const uuid&) = default;

		operator uint64_t() const { return m_uuid; }
	private:
		uint64_t m_uuid;
	};
}

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<spacewar::uuid>
	{
		std::size_t operator()(const spacewar::uuid& uuid) const noexcept
		{
			return uuid;
		}
	};

}


#endif //UUID_HPP
