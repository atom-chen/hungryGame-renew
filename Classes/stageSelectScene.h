#ifndef __STAGESELECT_SCENE_H__
#define __STAGESELECT_SCENE_H__
/*
* 2013 08 18
* Joung Daun
* Stage Select
*/
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class stageSelectScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();
    
   
	void stageMenu(Object* pSender);
	void menuGoBackCallback(Object* pSender);
	void onExit();
	void goStageScene();
	void doMsgRecv(Object* obj);
	int sStageNum; // for stage of each building
	int buildingNum;
    // implement the "static node()" method manually
	CREATE_FUNC(stageSelectScene);
};

#endif  // __BUILDING_SCENE_H__
