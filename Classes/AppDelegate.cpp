#include "AppDelegate.h"
#include "SceneInit.h"
#include "DataManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("XP");
        director->setOpenGLView(glview);
    }

	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(480, 320, ResolutionPolicy::EXACT_FIT);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	//FileUtils::getInstance()->addSearchPath("");

    std::string jsonTable("Role");
    std::string jsonFile("Role.json");
    DataManager::getInstance()->readTableFromDataFile(jsonTable, jsonFile);
    CCLOG("!!!!! print table :");
    DataManager::getInstance()->printTable(jsonTable);
    
	SceneInit();

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
