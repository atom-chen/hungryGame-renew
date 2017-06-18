#ifndef __BUILDING_SCENE_H__
#define __BUILDING_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

class BuildingScene : public cocos2d::LayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();
    
    // a selector callback
	void menuGoBackCallback(cocos2d::Ref* pSender);
    
    void menuBuildFunction(cocos2d::Ref* pSender);

	int buildingNum;

    // implement the "static node()" method manually
	CREATE_FUNC(BuildingScene);
};

#endif  // __BUILDING_SCENE_H__
