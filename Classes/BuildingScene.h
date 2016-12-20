#ifndef __BUILDING_SCENE_H__
#define __BUILDING_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class BuildingScene : public cocos2d::Layer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();
    
    // a selector callback
    void menuBuild1Callback(cocos2d::Object* pSender);
	void menuBuild2Callback(cocos2d::Object* pSender);
	void menuBuild3Callback(cocos2d::Object* pSender);
	void menuBuild4Callback(cocos2d::Object* pSender);
	void menuGoBackCallback(cocos2d::Object* pSender);

	int buildingNum;

    // implement the "static node()" method manually
	CREATE_FUNC(BuildingScene);
};

#endif  // __BUILDING_SCENE_H__
