#ifndef MAINSYSTEM_HPP
#define MAINSYSTEM_HPP
#include "Clock.hpp"

class MainSystem
{
public:
	enum error_t : uint8_t
	{
		SYSTEM_ERROR,
		SYSTEM_OKAY,
		SYSTEM_EXIT
	};
private:
	sClock clock;
public:
	virtual ~MainSystem() = default;
	error_t run(); // The actual main loop
	virtual error_t update(STime& deltaTime) = 0;
	virtual error_t render() = 0;
	virtual error_t startup() = 0;
	virtual error_t cleanup() = 0;
};

#endif // MAINSYSTEM_HPP
