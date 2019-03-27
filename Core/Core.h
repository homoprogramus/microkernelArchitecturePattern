#pragma once

#include <Windows.h>
#include <map>
#include <string>
#include <vector>

#include "Plugin.h"

class Core
{
public:
	__declspec(dllexport) Core();
	__declspec(dllexport) ~Core();

	__declspec(dllexport) void loadPlugin(std::string path);
private:
	void unloadPlugins();

	std::vector<HINSTANCE> _plugins;
	std::map<std::string, std::vector<APlugin*>> _consummers;
};