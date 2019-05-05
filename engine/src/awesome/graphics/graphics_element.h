#pragma once

namespace awesome
{
	class IGraphicsElement
	{
	public:

		inline unsigned int id() const { return m_id; }

		virtual void bind() = 0;
		virtual void unbind() = 0;

		inline bool isValid() const { return m_id != 0; }

	protected:

		// element id
		unsigned int m_id{ 0 };
	};
}