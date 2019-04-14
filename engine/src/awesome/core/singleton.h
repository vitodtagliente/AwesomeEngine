#pragma once

#include <cassert>

namespace awesome
{
	template<typename T>
	class Singleton
	{
	public:

		static T* instance() { return m_instance; }

	protected:

		Singleton()
		{
			assert(m_instance == nullptr);
			m_instance = static_cast<T*>(this);
		}
		~Singleton()
		{
			m_instance = nullptr;
		}

		static T* m_instance;
	};

	template<typename T>
	T* Singleton<T>::m_instance(nullptr);
}