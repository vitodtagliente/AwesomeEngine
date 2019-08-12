#pragma once

namespace awesome
{
	template <typename T>
	class ServiceLocator
	{
	public:

		static T* const instance() { return m_service; }

		static void provide(T* const t_service)
		{
			m_service = t_service;
		}

	private:

		static T* m_service;
	};
}