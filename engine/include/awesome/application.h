#pragma once

namespace Awesome
{
	class Application
	{
	private:
		static Application* singleton;

		bool running{ false };

	public:

		Application();
		~Application();

		static Application* instance();

		bool isRunning() const;

		virtual void init() = 0;
		virtual void render() = 0;
		virtual void update(float deltaTime) = 0;

		void close();
	};
}