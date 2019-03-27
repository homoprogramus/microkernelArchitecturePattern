#pragma once

#include <map>

#define DLL_EXPORT __declspec(dllexport)

class AEvent
{
public:
	DLL_EXPORT static AEvent* makeEvent(std::string eventName);
	DLL_EXPORT static AEvent* addPrototype(std::string eventName, AEvent* event);

	DLL_EXPORT virtual ~AEvent() = 0
	{};

	DLL_EXPORT std::string toString();

	DLL_EXPORT virtual AEvent* clone() const = 0;

private:
	static std::map<std::string, AEvent*> _protoTable;
};