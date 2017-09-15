#ifndef __STAGESELECT_SCENE_H__
#define __STAGESELECT_SCENE_H__
/*
* 2013 08 18
* Joung Daun
* Stage Select
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

class stageSelectScene : public LayerColor
{
public:
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();

    // implement the "static node()" method manually
    CREATE_FUNC(stageSelectScene);
private:
    int sStageNum; // for stage of each building
    int buildingNum;
    
private:
    void stageMenu(Ref* pSender);
    void menuGoBackCallback(Ref* pSender);
    void goStageScene();
};

#endif  // __BUILDING_SCENE_H__
