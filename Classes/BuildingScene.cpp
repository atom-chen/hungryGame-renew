/*
	∫Ùµ˘º±≈√√¢
 */

#include "BuildingScene.h"
#include "music.h"
#include "mainScene.h"
#include "stageSelectScene.h"

using namespace cocos2d;
using namespace cocos2d::ui;

Scene* BuildingScene::createScene()
{
    Scene * scene = NULL;
    // 'scene' is an autorelease object
    scene = Scene::create();
    
    // 'layer' is an autorelease object
    BuildingScene *layer = BuildingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BuildingScene::init()
{
    if(! LayerColor::initWithColor(Color4B(242,241,218,255)))
    {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    buildingNum = 0;
    Sprite* pBuildingBg = Sprite::create("img/buildingSelect_bg.png");
    
    // Place the sprite on the center of the screen
    pBuildingBg->setPosition(Vec2(size.width/2, size.height/2));
    pBuildingBg->setScale(size.width/pBuildingBg->getContentSize().width);
    
    // Add the sprite to HelloWorld layer as a child layer.
    this->addChild(pBuildingBg, 0);
    
    //image scale factor
    float scaleF = 2.0f;
    
    auto game1Btn = Button::create("img/buildingSelect_btn_b1.png", "img/buildingSelect_btn_b1_n.png");
    game1Btn->setPosition(Vec2(300, 1200));
    game1Btn->setScale(scaleF);
    game1Btn->setTag(1);
    game1Btn->addClickEventListener(CC_CALLBACK_1(BuildingScene::menuBuildFunction, this));
    this->addChild(game1Btn);
    
    auto game2Btn = Button::create("img/buildingSelect_btn_b2.png", "img/buildingSelect_btn_b2_n.png");
    game2Btn->setPosition(Vec2(800, 1200));
    game2Btn->setScale(scaleF);
    game2Btn->setTag(2);
    this->addChild(game2Btn);
    
    auto game3Btn = Button::create("img/buildingSelect_btn_b3.png", "img/buildingSelect_btn_b3_n.png");
    game3Btn->setPosition(Vec2(300, 600));
    game3Btn->setScale(scaleF);
    game3Btn->setTag(3);
    this->addChild(game3Btn);
    
    auto game4Btn = Button::create("img/buildingSelect_btn_b4.png", "img/buildingSelect_btn_b4_n.png");
    game4Btn->setPosition(Vec2(800, 600));
    game4Btn->setScale(scaleF);
    game4Btn->setTag(4);
    this->addChild(game4Btn);
    
    auto backBtn = Button::create("img/btn_goBack.png", "img/btn_goBack_n.png");
    backBtn->setPosition(Vec2(200, size.height-200));
    backBtn->setScale(scaleF);
    this->addChild(backBtn);
    
    return true;
}


void BuildingScene::menuBuildFunction(cocos2d::Ref *pSender)
{
    Button *item = (Button*)pSender;
    int tag = item->getTag();
    buildingNum = tag*10;
    // make scene
    Scene *pScene = stageSelectScene::createScene();
    auto trans = TransitionFade::create(0.5, pScene);
    Director::getInstance()->replaceScene(trans);
}

//µ«µπæ∆∞°±‚
void BuildingScene::menuGoBackCallback(Ref* pSender)
{
    music m;
    m.effectStart("sound/effect_btn_click.mp3");
    
    Scene *pScene = mainScene::createScene();
    auto trans = TransitionFade::create(0.5f, pScene);
    Director::getInstance()->replaceScene(trans);
}

