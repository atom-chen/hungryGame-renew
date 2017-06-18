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

// on "init" you need to initialize your instance
bool stageSelectScene::init()
{
    if(! LayerColor::initWithColor(Color4B(242,241,218,255)))
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    //sStageNum = 0;
    
    if(!UserDefault::getInstance()->getIntegerForKey("lastStage"))
    {
        UserDefault::getInstance()->setIntegerForKey("lastStage",10);
        UserDefault::getInstance()->flush();
    }
    
    //πË∞Ê ¿ÃπÃ¡ˆ ª˝º∫
    Sprite* pStageBg = Sprite::create("img/stageSelect/stage_bg.png");
    pStageBg->setScale(size.width/pStageBg->getContentSize().width);
    
    // Place the sprite on the center of the screen
    pStageBg->setPosition(Vec2(size.width/2, size.height/2));
    
    // Add the sprite to HelloWorld layer as a child layer.
    this->addChild(pStageBg, 0);
    
    //for stageNum of each building
    
    Vector<MenuItem*> menuVector;
    for(int i=0; i<9;i++)
    {
        std::string img1 = StringUtils::format("img/stageSelect/stage_btn_%d.png", i+1);
        std::string img2 = StringUtils::format("img/stageSelect/stage_btn_%d_n.png", i+1);
        auto menuBtn = MenuItemImage::create(img1, img2, this,
                                             menu_selector(stageSelectScene::stageMenu));
        menuBtn->setPosition(Vec2(size.width*(0.2+0.3*(i%3)), size.height*(0.8-0.2*(i/3))));
        menuBtn->setScale(1.5);
        menuBtn->setTag(i);
        menuVector.pushBack(menuBtn);
    }
    
    Menu *stageMenu = Menu::createWithArray(menuVector);
    stageMenu->setPosition(Vec2());
    
    this->addChild(stageMenu,1);
    
    
    //µ«µπæ∆∞°±‚ πˆ∆∞
    MenuItemImage *pGoBack = MenuItemImage::create(
                                                   "img/btn_goBack.png",
                                                   "img/btn_goBack_n.png",
                                                   this,
                                                   menu_selector(stageSelectScene::menuGoBackCallback));
    
    // Place the menu item bottom-right conner.
    pGoBack->setPosition(Vec2(size.width/1.25, size.height/14.28));
    
    // Create a menu with the "close" menu item, it's an auto release object.
    Menu* pGoBackMenu = Menu::create(pGoBack, NULL);
    pGoBackMenu->setPosition(Vec2());
    
    // Add the menu to HelloWorld layer as a child layer.
    this->addChild(pGoBackMenu, 1);
    
    __NotificationCenter::getInstance()->addObserver(this,
                                                     callfuncO_selector(stageSelectScene::doMsgRecv),
                                                     "BuildingNoti", NULL);
    
    return true;
}

void stageSelectScene::stageMenu(Ref* pSender)
{
    music m;
    m.effectStart("sound/effect_btn_click.mp3");
    /***
     ø©±‚ø° ∞‘¿” »≠∏È¿∏∑Œ ¿¸»Ø«œ¥¬∞≈ µÈæÓ∞®!!
     ****/
    int check;
    int dechk;
    MenuItem *pGet = (MenuItem *)pSender;
    dechk = pGet->getTag();
    sStageNum = buildingNum + dechk;
    check = UserDefault::getInstance()->getIntegerForKey("lastStage");
    if( check >= sStageNum )
        this->goStageScene();
}

//µ«µπæ∆∞°±‚
void stageSelectScene::menuGoBackCallback(Ref* pSender)
{
    Scene *pScene = BuildingScene::createScene();
    auto trans = TransitionFade::create(0.5, pScene);
    Director::getInstance()->replaceScene(trans);
}

void stageSelectScene::doMsgRecv(Ref* obj)
{
    String* pParam = (String*)obj;
    int flag = pParam->intValue();
    if(flag>0)
        buildingNum = flag;
}
void stageSelectScene::onExit()
{
    Layer::onExit();
    __NotificationCenter::getInstance()->removeObserver(this, "BuildingNoti");
}
void stageSelectScene::goStageScene()
{
    UserDefault::getInstance()->setIntegerForKey("curStage",sStageNum);
    UserDefault::getInstance()->flush();
    Scene* pScene = gameScene::createScene();
    auto trans = TransitionFade::create(0.5, pScene);
    Director::getInstance()->replaceScene(trans);
}
