#pragma once

#include <string>
#include "../types.h"

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
	namespace data
	{
		class StringId 
		{
		private:

			uint32 m_hash{ 0 };

			void computeHash(const std::string& str) {
				for (auto& it : str) {
					// be sure to use prime numbers
					m_hash = 37 * m_hash + 17 * static_cast<char>(it);
				}
			}

		public:

			StringId(const std::string& str) {
				computeHash(str);
			}

			StringId(const char* str) {
				computeHash(std::string{ str });
			}

			~StringId() = default;

			StringId(const StringId& other) = delete;			

			inline StringId& operator= (const StringId& other) {
				if (*this != other) {
					m_hash = other.m_hash;
				}
				return *this;
			}

			StringId& operator=(StringId&& str) = default;
			StringId(StringId&& str) = default;

			inline bool operator== (const StringId& other) const
			{
				return m_hash == other.m_hash;
			}

			inline bool operator!= (const StringId& other) const
			{
				return m_hash != other.m_hash;
			}
		};
	}
}