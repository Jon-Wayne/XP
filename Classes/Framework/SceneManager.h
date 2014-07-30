#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "Base.h"

class Controller;

class SceneManager : public Ref
{
private:
	SceneManager();
public:
	static SceneManager *getInstance();
	bool init();
	~SceneManager();

	void push(std::string name, Ref *date);
	void pop();
    void popToScene(std::string name);
    void replace(std::string name, Ref *data);
    void removeScene(int index, bool isPop);
    void removeScene(int index);
    void resumeScene(int index);
    
    void refreshTopScene();
    
    Controller *getTopScene();
    
    void printStack();

	Scene *getRootScene(){ return _rootScene; };
private:
	Scene *_rootScene;
    
    std::vector<std::string>    _nameStack;
    Vector<Controller *>        _cntrStack;
    Vector<Ref *>               _dataStack;
    int                         _size;
};

#endif //__SCENE_MANAGER_H__