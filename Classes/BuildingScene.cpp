/*
	∫Ùµ˘º±≈√√¢
 */

#include "BuildingScene.h"
#include "music.h"
#include "mainScene.h"
#include "stageSelectScene.h"

using namespace cocos2d;

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
    float scaleF = 1.7f;
    
    //√ππ¯¬∞ ∞«π∞πˆ∆∞
    MenuItemImage *pBuilding_1 = MenuItemImage::create(
                                                       "img/buildingSelect_btn_b1.png",
                                                       "img/buildingSelect_btn_b1_n.png",
                                                       this,
                                                       menu_selector(BuildingScene::menuBuildFunction));
    
    // Place the menu item bottom-right conner.
    pBuilding_1->setPosition(Vec2(size.width/3.33, size.height/1.53));
    pBuilding_1->setScale(scaleF);
    pBuilding_1->setTag(1);
    
    //µŒπ¯¬∞ ∞«π∞πˆ∆∞
    MenuItemImage *pBuilding_2 = MenuItemImage::create(
                                                       "img/buildingSelect_btn_b2.png",
                                                       "img/buildingSelect_btn_b2_n.png",
                                                       this,
                                                       menu_selector(BuildingScene::menuBuildFunction));
    
    // Place the menu item bottom-right conner.
    pBuilding_2->setPosition(Vec2(size.width/1.42, size.height/1.53));
    pBuilding_2->setScale(scaleF);
    pBuilding_2->setTag(2);
    
    MenuItemImage *pBuilding_3 = MenuItemImage::create(
                                                       "img/buildingSelect_btn_b3.png",
                                                       "img/buildingSelect_btn_b3_n.png",
                                                       this,
                                                       menu_selector(BuildingScene::menuBuildFunction));
    
    // Place the menu item bottom-right conner.
    pBuilding_3->setPosition(Vec2(size.width/3.33, size.height/3.33));
    pBuilding_3->setScale(scaleF);
    pBuilding_3->setTag(3);
    
    MenuItemImage *pBuilding_4 = MenuItemImage::create(
                                                       "img/buildingSelect_btn_b4.png",
                                                       "img/buildingSelect_btn_b4_n.png",
                                                       this,
                                                       menu_selector(BuildingScene::menuBuildFunction));
    
    // Place the menu item bottom-right conner.
    pBuilding_4->setPosition(Vec2(size.width/1.42, size.height/3.33));
    pBuilding_4->setScale(scaleF);
    pBuilding_4->setTag(4);
    
    //µ«µπæ∆∞°±‚ πˆ∆∞
    MenuItemImage *pGoBack = MenuItemImage::create(
                                                   "img/btn_goBack.png",
                                                   "img/btn_goBack_n.png",
                                                   this,
                                                   menu_selector(BuildingScene::menuGoBackCallback));
    
    // Place the menu item bottom-right conner.
    pGoBack->setPosition(Vec2(size.width/1.25, size.height/14.28));
    pGoBack->setScale(scaleF);
    
    Menu* pMenu = Menu::create(pBuilding_1, pBuilding_2, pBuilding_3, pBuilding_4, pGoBack, NULL);
    pMenu->setPosition(Vec2());
    this->addChild(pMenu, 1);
    
    return true;
}


void BuildingScene::menuBuildFunction(cocos2d::Ref *pSender)
{
    MenuItem *item = (MenuItem*)pSender;
    int tag = item->getTag();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/effect_btn_click.mp3");
    Scene *pScene = stageSelectScene::createScene();
    buildingNum = tag*10;
    String* popParam = String::create(StringUtils::format("%d",buildingNum));
    __NotificationCenter::getInstance()->postNotification("BuildingNoti", popParam);
    
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

