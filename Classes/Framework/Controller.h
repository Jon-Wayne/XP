#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

#include "CocosGUI.h"
using namespace cocos2d::ui;

#include "Base.h"

class Controller : public Ref
{
public:
	Controller();
	virtual ~Controller();
    
    virtual void init(Ref *data){};

	virtual std::string getName(){ return _name; };
	virtual bool isRemoveBefore(){ return true; };
    
    virtual std::vector<std::string> *expectedEvents(){ return NULL; };
    virtual void handleEvent(std::string event, Ref *data){};
    void dispatchEvent(std::string event, Ref *data);
    
    virtual void reset(){};
    virtual void refresh(){};
    
	virtual void viewLoad(){};
	virtual void viewAppear(){};
	virtual void viewDisappear(){};
	virtual void viewUnload(){};
    
    Widget *loadScene(std::string jsonFileName);
    void sceneAdpat(Node *scene);
    
    void test(){ CCLOG("Controller:test %s", _name.c_str()); };

	Scene *getScene(){ return _scene; };
    Ref *getData();
    void setData(Ref *data);
protected:
    std::string _name;
	Scene       *_scene;
    Ref         *_data;
};



typedef Controller *(*FactoryCreate_PTR)(Ref *data);

#define DECLARE_CLASS_CREATE(class_name)\
	static Controller *Create##class_name(Ref *data);

#define IMP_CLASS_CREATE(class_name)\
	Controller *class_name::Create##class_name(Ref *data)\
	{\
		Controller *controller = new class_name();\
        controller->init(data);\
		controller->autorelease();\
		return controller;\
	}



#endif //__CONTROLLER_H__