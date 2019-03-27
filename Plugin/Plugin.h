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

	DLL_EXPORT void link(std::vector<APlugin*>* consummers);
	DLL_EXPORT void send();

	DLL_EXPORT virtual void receive(std::shared_ptr<AEvent>) = 0;
	DLL_EXPORT virtual std::string getEventType() = 0;
	DLL_EXPORT virtual void unregisterPlugin() = 0;

protected:
	DLL_EXPORT virtual std::shared_ptr<AEvent> _createEvent() = 0;

private:
	std::vector<APlugin*> _consummers;
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