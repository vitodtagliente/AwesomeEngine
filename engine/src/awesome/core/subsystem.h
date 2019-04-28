#pragma once

namespace awesome
{
	// generic Engine Subsystem interface
	class ISubsystem
	{
	public:
		
		// module initialization 
		virtual void startup() = 0;
		virtual void shutdown() = 0;
		// update the module
		virtual void update(const double t_deltaTime) = 0;
		
	};

	template<typename T>
	class Subsystem : public ISubsystem
	{
	public:

		Subsystem() { m_instance = this; }
		~Subsystem() { m_instance = nullptr; }

		// module singleton instance 
		static T* instance() { return m_instance; }

	private:

		// module instance 
		static T* m_instance;
	};

	template<typename T>
	T* Subsystem<T>::m_instance(nullptr);
}