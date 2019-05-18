#pragma once

#include <string>

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
	public:

		StringId();
		StringId(const std::string& t_data);
		~StringId();

		inline const std::string& data() const { return m_data; }

		inline bool operator== (const StringId& t_other) const
		{
			return m_hash == t_other.m_hash;
		}

		inline bool operator!= (const StringId& t_other) const
		{
			return m_hash != t_other.m_hash;
		}

		static const StringId None;

	private:

		// hashed data
		unsigned int m_hash;
		// native data
		std::string m_data;
	};
}