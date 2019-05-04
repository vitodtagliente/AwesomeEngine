#pragma once

#include <string>
#include "../core/types.h"

/*
	Strings require more memory, dynamic memory allocation and
	are more expensive to compare than pure integers. Seeing
	as any game/graphics related engine has heavy requirements
	on those 3 mentioned points deciding on a proper unique
	identification scheme is quite relevant.
	
	We create a hash function to integer conversion.
	Note that hashing is relatively expensive;
	it's best to hash a string to get its unique
	and use the integer id for all further computations.
*/

namespace awesome
{
	class StringId final
	{
		StringId(const std::string& t_data)
			: m_hash()
			, m_data(t_data)
		{
			for (const auto& it : t_data) 
			{
				// be sure to use prime numbers
				m_hash = 37 * m_hash + 17 * static_cast<char>(it);
			}
		}
		~StringId() = default;

		const std::string& data() const { return m_data; }

		inline bool operator== (const StringId& t_other) const
		{
			return m_hash == t_other.m_hash;
		}

		inline bool operator!= (const StringId& t_other) const
		{
			return m_hash != t_other.m_hash;
		}

	private:

		// hashed data
		uint32 m_hash;
		// native data
		std::string m_data;
	};
}