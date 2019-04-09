#pragma once

#include <grandel/grandel.h>

namespace examples
{
	using namespace grandel;
	using namespace grandel::data;

	class TestInputBehaviour : public ApplicationBehaviour
	{
	private:
		int i = 0;

	public:

		void update() override {

			if (Input::isKeyPressed(KeyCode::E)) {
				log(LogSeverity::Log, "E Pressed");
			}
			if (Input::isKeyDown(KeyCode::W)) {
				log(LogSeverity::Log, "Holding Down W");
			}
			if (Input::isKeyReleased(KeyCode::Q)) {
				log(LogSeverity::Log, "Q Released");
			}
			if (Input::isKeyPressed(KeyCode::Space)) {
				Application::instance()->close();
			}

			if (Input::isKeyPressed(KeyCode::MouseButtonLeft)) {
				log(LogSeverity::Warning, "Left Mouse Button Clicked");
				i = 0;
			}
			if (Input::isKeyReleased(KeyCode::MouseButtonLeft)) {
				log(LogSeverity::Log, "Left Mouse Button Released");
			}
			if (Input::isKeyDown(KeyCode::MouseButtonLeft)) {
				if (i == 0) log(LogSeverity::Log, "Clicking Left Mouse Button");
				++i;
			}
			if (Input::isKeyPressed(KeyCode::MouseButtonRight)) {
				log(LogSeverity::Log, "Right Mouse Button Clicked");
			}
			if (Input::isKeyPressed(KeyCode::MouseButtonWheel)) {
				log(LogSeverity::Log, "Wheel Mouse Button Clicked");
			}
		}
	};
}