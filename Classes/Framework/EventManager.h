#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include "Base.h"

class Controller;

class EventManager : public Ref
{
private:
	EventManager();
public:
	static EventManager *getInstance();
	bool init();
	~EventManager();

	void addListener(std::string event, Controller *listener);
    void removeListener(Controller *listener);
    void dispatchEvent(std::string event, Ref *data);
private:
    std::map<std::string, Controller *> _eventToListeners;
    std::map<Controller *, std::string> _listenersToEvent;
};

#endif //__EVENT_MANAGER_H__