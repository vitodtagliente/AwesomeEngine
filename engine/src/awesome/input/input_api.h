#pragma once

namespace awesome
{
	class InputAPI
	{
	public:

		enum class Type
		{
			Null,
			GLFW,
			Android
		};

		InputAPI(const Type t_type)
			: m_type(t_type)
		{

		}
		~InputAPI() = default;

		virtual bool startup() = 0;
		virtual void shutdown() = 0;

		inline Type getType() const { return m_type; }

	private:

		// api type
		Type m_type;
	};
}