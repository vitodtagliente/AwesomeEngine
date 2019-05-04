#pragma once

namespace awesome
{
	template<typename T>
	class Singleton
	{
	public:

		Singleton() { m_instance = dynamic_cast<T*>(this); }
		virtual ~Singleton() { m_instance = nullptr; }

		// get the singleton instance 
		static T* instance() { return m_instance; }

	private:

		// singleton instance 
		static T* m_instance;
	};

	template<typename T>
	T* Singleton<T>::m_instance(nullptr);
}