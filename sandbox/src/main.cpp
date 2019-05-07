/*
 * Engine examples
 * This is a test sandbox application
 */

#include <awesome/awesome.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <direct.h>
#include "sandbox_game.h"

using namespace awesome;
using namespace std;

std::string current_working_directory()
{
	char* cwd = _getcwd(0, 0); // **** microsoft specific ****
	std::string working_directory(cwd);
	std::free(cwd);
	return working_directory;
}

int main()
{
	cout << current_working_directory() << endl;
	std::string path = current_working_directory();
	for (const auto& entry : std::filesystem::directory_iterator(path))
		std::cout << entry.path() << std::endl;

	Engine::run({ new SandboxGame() });
	return 0;
}