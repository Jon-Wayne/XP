#include "ControllerFactory.h"

static ControllerFactory *s_pControllerFactory = NULL;

ControllerFactory *ControllerFactory::getInstance()
{
	if (!s_pControllerFactory)
	{
		s_pControllerFactory = new ControllerFactory();
	}

	return s_pControllerFactory;
}

void ControllerFactory::registerFactoryCreate(std::string name, FactoryCreate_PTR fc_ptr)
{
	std::map<std::string, FactoryCreate_PTR>::iterator it = 
		_registeredClassMap.find(name);
	
	if (it == _registeredClassMap.end())
		_registeredClassMap.insert(
			std::pair<std::string, FactoryCreate_PTR>(name, fc_ptr));
	else
		CCLOG("the key"" %s "" have already exist!", name.c_str());
}

Controller *ControllerFactory::getController(std::string name, Ref *data)
{
	std::map<std::string, FactoryCreate_PTR>::iterator it;
    it = _registeredClassMap.find(name);
	
	if (it != _registeredClassMap.end())
	{
		//get the creation fucntion pointer
		FactoryCreate_PTR creater_ptr = it->second;
        
		//really create here
		//it's a autorelease object
		Controller *controller = creater_ptr(data);
		
		return controller;
	}
	else
	{
		CCLOG("The key "" %s "" doesn't exist!", name.c_str());
		return NULL;
	}
}

ControllerFactory::ControllerFactory()
{
    
}


ControllerFactory::~ControllerFactory()
{
	s_pControllerFactory = NULL;
}

