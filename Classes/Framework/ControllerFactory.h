#ifndef __CONTROLLER_FACTORY_H__
#define __CONTROLLER_FACTORY_H__

#include "Base.h"
#include "Controller.h"

class Controller;

class ControllerFactory : public Ref
{
public:
	static ControllerFactory *getInstance();
	
	ControllerFactory();
	~ControllerFactory();

	void registerFactoryCreate(std::string name, FactoryCreate_PTR fc_ptr);

	Controller *getController(std::string name, Ref *data);

private:
	std::map<std::string, FactoryCreate_PTR> _registeredClassMap;
};

#endif //__CONTROLLER_FACTORY_H__