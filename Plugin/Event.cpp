#include "Event.h"

std::map<std::string, AEvent*> AEvent::_protoTable;

AEvent* AEvent::makeEvent(std::string eventName)
{
	auto it = _protoTable.find(eventName);
	
	if(it == _protoTable.end())
		return nullptr;

	return it->second->clone();
}

AEvent* AEvent::addPrototype(std::string eventName, AEvent* event)
{
	if(_protoTable.count(eventName) == 0)
		_protoTable.insert(std::pair<std::string, AEvent*>(eventName, event));
	return event;
}

std::string AEvent::toString()
{
	return "AEvent";
}