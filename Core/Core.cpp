#include "Core.h"

Core::Core()
{}

Core::~Core()
{
	for (auto it : _consummers)
	{
		for (APlugin* plugin : it.second)
			plugin->unregisterPlugin();
	}

	unloadPlugins();
}

void Core::loadPlugin(std::string path)
{
	HINSTANCE lib;
	lib = LoadLibrary(std::wstring(path.begin(), path.end()).c_str());
	if (lib == nullptr)
	{
		throw std::runtime_error("");
		return;
	}
	_plugins.push_back(lib);

	PluginDetails* details = (PluginDetails*)GetProcAddress(lib, "exports");
	if (details == nullptr)
	{
		throw std::runtime_error("");
		return;
	}

	if (details->apiVersion >= PLUGIN_API_VERSION)
	{
		throw std::runtime_error("");
		return;
	}

	APlugin* plugin = details->initializeFunction();
}

void Core::unloadPlugins()
{
	for (HINSTANCE lib : _plugins)
		bool freeResult = FreeLibrary(lib);
}
