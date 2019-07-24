#pragma once

#include <functional>
#include <map>

template <typename... Args>
class Signal
{
public:
	Signal() : _currentID{0}
	{}

	Signal(Signal const& other) : _currentID{0}
	{}

	Signal& operator=(Signal const& other)
	{
		disconnectAll();
	}

	/**
	 * Connect a member function to this signal
	 */
	template <typename T>
	int connect(T* inst, void (T::* funct)(Args...))
	{
		return connect([=](Args... args)
		{
			(inst->*funct)(args...);
		});
	}

	/**
	 * Connect a const member function to this signal
	 */
	template <typename T>
	int connect(T* inst, void (T::*funct)(Args...) const)
	{
		return connect([=](Args... args)
		{
			(inst->*funct)(args...);
		});
	}

	/**
	 * Connect std::function to this signal
	 */
	int connect(std::function<void(Args...)> const &slot) const
	{
		_slots.insert(std::make_pair(++_currentID, slot));
		return _currentID;
	}

	/**
	 * Disconnect a previously connected function
	 */
	void disconnect(int id) const
	{
		_slots.erase(id);
	}

	/**
	 * Disconnect all previously connected functions
	 */
	void disconnectAll() const
	{
		_slots.clear();
	}

	/**
	 * Call all connected functions
	 */
	void emit(Args... p)
	{
		for (std::pair<int, std::function<void(Args...)>> i : _slots)
			i.second(p...);
	}

private:
	std::map<int, std::function<void(Args...)>> _slots;
	int _currentID;
};