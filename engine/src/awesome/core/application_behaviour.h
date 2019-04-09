#pragma once

/*
 * Application custom behaviours interface
 */

namespace awesome
{
	class ApplicationBehaviour
	{
	protected:
		bool m_Active{ true };

	public:

		ApplicationBehaviour() = default;
		virtual ~ApplicationBehaviour() = default;

		ApplicationBehaviour& operator=(ApplicationBehaviour&& application_behaviour) = default;
		ApplicationBehaviour(const ApplicationBehaviour& application_behaviour) = default;
		ApplicationBehaviour(ApplicationBehaviour&& application_behaviour) = default;
		ApplicationBehaviour& operator= (const ApplicationBehaviour& application_behaviour) = default;		
		
		virtual void init() {}
		virtual void update() {}
		virtual void uninit() {}

		inline bool isActive() const { return m_Active; }
	};
}