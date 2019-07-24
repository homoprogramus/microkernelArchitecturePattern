#pragma once

#include <vector>
#include <future>

#include "Event.h"

constexpr int PLUGIN_API_VERSION = 1;

class APlugin
{
public:
	DLL_EXPORT virtual ~APlugin() = 0
	{};

	DLL_EXPORT virtual void unregisterPlugin() = 0;
};

struct PluginDetails
{
	int apiVersion;
	const char* className;
	const char* pluginName;
	const char* pluginVersion;
	APlugin*(*initializeFunction)();
};

#define PLUGIN(classType, pluginName, pluginVersion)	\
extern "C"												\
{														\
	DLL_EXPORT APlugin* getPlugin()						\
	{													\
		static classType plugin;						\
		return &plugin;									\
	}													\
														\
	DLL_EXPORT PluginDetails exports =					\
	{													\
		PLUGIN_API_VERSION,								\
		#classType,										\
		pluginName,										\
		pluginVersion,									\
		getPlugin										\
	};													\
}