#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class mainScene : public LayerColor
{
public:
    virtual bool init();  

    static cocos2d::Scene* createScene();

    //menu button callback
    void menuBtnsCallback(Ref* pSender, ui::Button::TouchEventType type);

    // implement the "static node()" method manually
    CREATE_FUNC(mainScene);
};

#endif  // __MAIN_SCENE_H__
