#include <iostream>
#include <conio.h>

#include "PluginLoader.h"

#include "IPlugin.h"

int main(int argc, char** argv)
{
	FlakedTuna::PluginLoader loader;

	// Modify this line to match your target output director of the Plugin Example DLL!
	loader.FindPluginsAtDirectory("C:\\Source\\FlakedTuna\\Example\\Release\\", "dll");

	std::vector<std::shared_ptr<IPlugin>> plugins = loader.BuildAndResolvePlugin<IPlugin>();

	for (auto iter : plugins)
	{
		std::cout << iter->GetString() << std::endl;
	}

	_getch();
	return 0;
}