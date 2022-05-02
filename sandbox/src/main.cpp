/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <filesystem>

#include "game.h"

int main()
{
	Application::Settings settings;
	if (std::filesystem::exists("settings.json"))
	{
		settings = Application::Settings::load("settings.json");
	}
	else
	{
		settings.fps = FpsMode::Fps60;
		settings.mode = Application::Mode::Editor;
		settings.workspacePath = std::filesystem::current_path() / ".." / "assets";
	}

	Application& app = Application::instance();
	app.init(settings, { new Game() });
	const int result = app.run();
	return result;
}