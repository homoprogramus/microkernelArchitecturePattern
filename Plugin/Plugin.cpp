#include "Plugin.h"

void APlugin::link(std::vector<APlugin*>* consummers)
{
	for (APlugin* plugin : *consummers)
		_consummers.push_back(plugin);
}

void APlugin::send()
{
	std::shared_ptr<AEvent> event = _createEvent();//create the event
	for(APlugin* plugin : _consummers)
		std::async(&APlugin::receive, plugin, event);//call all receive functions async
}