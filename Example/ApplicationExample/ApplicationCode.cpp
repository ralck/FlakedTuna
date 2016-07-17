#include <iostream>

#if defined(WIN32) || defined(_WIN32)
#include <conio.h>
#endif

#include "PluginLoader.h"

#include "IPlugin.h"

int main(int argc, char** argv)
{
	FlakedTuna::PluginLoader loader;

	// Modify this line to match your target output director of the Plugin Example DLL!
	loader.FindPluginsAtDirectory("C:\\Source\\FlakedTuna\\Example\\Release\\", "dll");
	//loader.FindPluginsAtDirectory("./", "so");

	std::vector<std::shared_ptr<IPlugin>> plugins = loader.BuildAndResolvePlugin<IPlugin>();

	for (auto iter : plugins)
	{
		std::cout << iter->GetString() << std::endl;
	}

#if defined(WIN32) || defined(_WIN32)
	_getch();
#endif

	return 0;
}