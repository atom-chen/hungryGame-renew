/*
 * 2013 08 18
 * Joung Daun
 * Stage Select
 */
#include "stageSelectScene.h"
#include "music.h"
#include "mainScene.h"
#include "BuildingScene.h"
#include "stageSelectScene.h"
#include "gameScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scene* stageSelectScene::createScene()
{
    Scene * scene = Scene::create();
    
    // 'layer' is an autorelease object
    stageSelectScene *layer = stageSelectScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool stageSelectScene::init()
{
    if(! LayerColor::initWithColor(Color4B(242,241,218,255)))
    {
        return false;
    }
    
    //image scale factor
    const float scaleF = 1.7f;
    
    Size size = Director::getInstance()->getVisibleSize();
    
    if(!UserDefault::getInstance()->getIntegerForKey("lastStage"))
    {
        UserDefault::getInstance()->setIntegerForKey("lastStage", 10);
        UserDefault::getInstance()->flush();
    }
    
    buildingNum = UserDefault::getInstance()->getIntegerForKey("buildingNum");
    int lastStageNum = UserDefault::getInstance()->getIntegerForKey("lastStage");
    
    Sprite* pStageBg = Sprite::create("img/stageSelect/stage_bg.png");
    pStageBg->setScale(size.width/pStageBg->getContentSize().width);
    pStageBg->setPosition(Vec2(size.width/2, size.height/2));
    this->addChild(pStageBg, 0);
    
    //for stageNum of each building
    
    for(int i=0; i<9; i++)
    {
        std::string img1 = StringUtils::format("img/stageSelect/stage_btn_%d.png", i+1);
        std::string img2 = StringUtils::format("img/stageSelect/stage_btn_%d_n.png", i+1);
        auto menuBtn = Button::create(img1, img2);
        menuBtn->setPosition(Vec2(size.width*(0.2+0.3*(i%3)), size.height*(0.8-0.2*(i/3))));
        menuBtn->setScale(scaleF);
        menuBtn->setTag(buildingNum + i);
        menuBtn->addClickEventListener(CC_CALLBACK_1(stageSelectScene::stageMenu, this));
        if(lastStageNum < (buildingNum+i))
            menuBtn->setEnabled(false);
        this->addChild(menuBtn);
    }

    auto backBtn = Button::create("img/btn_goBack.png","img/btn_goBack_n.png");
    backBtn->setScale(scaleF);
    backBtn->setPosition(Vec2(size.width-300, 200));
    backBtn->addClickEventListener(CC_CALLBACK_1(stageSelectScene::menuGoBackCallback, this));
    this->addChild(backBtn, 1);
    
    return true;
}

void stageSelectScene::stageMenu(Ref* pSender)
{
    auto btn = (Button*)pSender;
    sStageNum = btn->getTag();
    this->goStageScene();
}

void stageSelectScene::menuGoBackCallback(Ref* pSender)
{
    Scene *pScene = BuildingScene::createScene();
    auto trans = TransitionFade::create(0.5, pScene);
    Director::getInstance()->replaceScene(trans);
}

void stageSelectScene::goStageScene()
{
    //save curr stage number
    UserDefault::getInstance()->setIntegerForKey("curStage", sStageNum);
    UserDefault::getInstance()->flush();
    
    Scene* pScene = gameScene::createScene();
    auto trans = TransitionFade::create(0.5, pScene);
    Director::getInstance()->replaceScene(trans);
}
