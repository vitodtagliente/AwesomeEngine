#pragma once

namespace awesome
{
	class Input;
	class Time;
	class Window;

	class ApplicationAPI
	{
	public:

		enum class Type
		{
			Null,
			GLFW,
			Android
		};

		ApplicationAPI(const Type t_type)
			: m_type(t_type)
		{

		}
		~ApplicationAPI() = default;

		virtual bool startup() = 0;
		virtual void shutdown() = 0;

		inline Type getType() const { return m_type; }

		// create application's objects
		virtual Input* createInput() const = 0;
		virtual Time* createTime() const = 0;
		virtual Window* createWindow() const = 0;

	private:

		// api type
		Type m_type;
	};
}