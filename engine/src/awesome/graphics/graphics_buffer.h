#pragma once

namespace awesome
{
	class GraphicsBuffer
	{
	public:

		virtual void bind() = 0;
		virtual void unbind() = 0;

		inline unsigned int id() const { return m_id; }
		inline bool isValid() const { return m_id != 0; }

	protected:

		// buffer id
		unsigned int m_id{ 0 };
	};
}