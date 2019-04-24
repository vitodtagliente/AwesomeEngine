#pragma once

// Engine module interface

namespace awesome
{
	template<typename T>
	class Module
	{
	public:

		Module() { m_instance = this; }
		~Module() { m_instance = nullptr; }

		// module initialization 
		virtual void startup() = 0;
		virtual void shutdown() = 0;
		// update the module
		virtual void update(const double t_deltaTime) = 0;

		// module singleton instance 
		static T* instance() { return m_instance; }

	private:

		// module instance 
		static T* m_instance;
	};

	template<typename T>
	T* Module<T>::m_instance(nullptr);
}