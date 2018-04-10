#ifndef MAINSYSTEM_HPP
#define MAINSYSTEM_HPP
#include "Clock.hpp"

class MainSystem
{
public:
	enum : int
	{
		SYSTEM_ERROR,
		SYSTEM_OKAY,
		SYSTEM_EXIT
	};
private:
	sClock clock;
public:
	virtual ~MainSystem() = default;
	int run(); // The actual main loop
	virtual int update(Time& deltaTime) = 0;
	virtual int render() = 0;
	virtual bool startup() = 0;
	virtual bool cleanup() = 0;
};

#endif // MAINSYSTEM_HPP
