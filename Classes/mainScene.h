#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class mainScene : public cocos2d::LayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuOptionCallback(cocos2d::Ref* pSender);
	void menuHelpCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	void menuDevCallback(cocos2d::Ref* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(mainScene);
};

#endif  // __MAIN_SCENE_H__
