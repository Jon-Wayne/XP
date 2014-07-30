#include "EventManager.h"

static EventManager *s_pEventManager = NULL;

EventManager::EventManager()
{
    
}

 EventManager *EventManager::getInstance()
{
    if (!s_pEventManager) {
        s_pEventManager = new EventManager();
        s_pEventManager->init();
    }
    
    return s_pEventManager;
}

bool EventManager::init()
{
    return true;
}

EventManager::~EventManager()
{
    s_pEventManager = NULL;
}

void EventManager::addListener(std::string event, Controller *listener)
{
    
}
void EventManager::removeListener(Controller *listener)
{
    
}
void EventManager::dispatchEvent(std::string event, Ref *data)
{
    
}