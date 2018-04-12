#ifndef MAINSYSTEM_HPP
#define MAINSYSTEM_HPP
#include "Clock.hpp"
#include "../abstract/SettingContainer.hpp"

class MainSystem
{
public:
	enum error_t : uint8_t
	{
		SYSTEM_ERROR,
		SYSTEM_OKAY,
		SYSTEM_EXIT
	};
protected:
	sClock clock;
	const Abstract::sSettingContainer window;
	SDL_Event ev;
	bool exitSignal;
public:
	MainSystem(int w, int h, const char *title);
	virtual ~MainSystem();
	error_t run(); // The actual main loop
	virtual error_t update(STime& deltaTime) = 0;
	virtual error_t render() = 0;
	virtual error_t startup() = 0;
	virtual error_t cleanup() = 0;
	virtual error_t processWindowEvent(const SDL_Event& ev) = 0;
};

#endif // MAINSYSTEM_HPP
