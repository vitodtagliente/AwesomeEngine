#pragma once

#include <cassert>

namespace awesome
{
	template<typename T>
	class Singleton
	{
	public:

		Singleton() 
		{ 
			assert(m_instance == nullptr);
			m_instance = static_cast<T*>(this); 
		}

		virtual ~Singleton() 
		{ 
			m_instance = nullptr; 
		}

		// cannot move or copy
		Singleton& operator=(Singleton&&) = delete;
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		Singleton& operator= (const Singleton&) = delete;

		// get the singleton instance 
		static T* instance() { return m_instance; }

	private:

		// singleton instance 
		static T* m_instance;
	};

	template<typename T>
	T* Singleton<T>::m_instance(nullptr);
}