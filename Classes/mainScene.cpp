#include "mainScene.h"
#include "music.h"
#include "HelpScene.h"
#include "BuildingScene.h"
#include "MakerInfoScene.h"
#include "optionScene.h"

using namespace cocos2d;

Scene* mainScene::createScene()
{
    Scene *scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();

        // 'layer' is an autorelease object
		mainScene *layer = mainScene::create();

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool mainScene::init()
{
        if(! LayerColor::initWithColor(Color4B::WHITE))
        {
            return false;
        }

		Size size = Director::getInstance()->getWinSize();

		music mu;
		mu.bgStart("background.mp3");
        // 1. Add a menu item with "X" image, which is clicked to quit the program.

		// 메인화면 배경 이미지 생성
		Sprite *pMainBg = Sprite::create("img/main_bg.png");
		pMainBg->setPosition(Vec2(size.width/2, size.height/2));
        pMainBg->setScale(size.width/pMainBg->getContentSize().width);
		this->addChild(pMainBg, 1);


        // 게임종료 버튼
        MenuItemImage *pCloseItem = MenuItemImage::create(
            "img/main_btn_endgame.png",
            "img/main_btn_endgame_n.png",
            this,
			menu_selector(mainScene::menuCloseCallback));

        // Place the menu item bottom-right conner.
		pCloseItem->setPosition(Vec2(size.width / 2 , size.height / 14.2));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pMenu = Menu::create(pCloseItem, NULL);
        pMenu->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 2);

		MenuItemImage *pDevItem = MenuItemImage::create(
            "img/main_btn_info.png",
            "img/main_btn_info_n.png",
            this,
			menu_selector(mainScene::menuDevCallback));

        // Place the menu item bottom-right conner.
		pDevItem->setPosition(Vec2(size.width /2 , size.height /5.26 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pDevMenu = Menu::create(pDevItem, NULL);
        pDevMenu->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pDevMenu, 2);

		MenuItemImage *pOptionItem = MenuItemImage::create(
            "img/main_btn_option.png",
            "img/main_btn_option_c.png",
            this,
			menu_selector(mainScene::menuOptionCallback));

        // Place the menu item bottom-right conner.
		pOptionItem->setPosition(Vec2(size.width /2 , size.height /2.32 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pOptionMenu = Menu::create(pOptionItem, NULL);
        pOptionMenu->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pOptionMenu, 2);

		MenuItemImage *pHelpItem = MenuItemImage::create(
            "img/main_btn_help.png",
            "img/main_btn_help_n.png",
            this,
			menu_selector(mainScene::menuHelpCallback));

        // Place the menu item bottom-right conner.
		pHelpItem->setPosition(Vec2(size.width / 2 , size.height /3.22 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pHelpMenu = Menu::create(pHelpItem, NULL);
        pHelpMenu->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pHelpMenu, 2);

		MenuItemImage *pStartItem = MenuItemImage::create(
            "img/main_btn_gamestart.png",
            "img/main_btn_gamestart_c.png",
            this,
			menu_selector(mainScene::menuStartCallback));

        // Place the menu item bottom-right conner.
		pStartItem->setPosition(Vec2(size.width /2 , size.height /1.81 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pStartMenu = Menu::create(pStartItem, NULL);
        pStartMenu->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pStartMenu, 2);

    return true;
}

void mainScene::menuCloseCallback(Object* pSender)
{
    // "close" menu item clicked
	music m;
	m.effectStart("sound/effect_btn_click.mp3");
    Director::getInstance()->end();
}

void mainScene::menuOptionCallback(Object* pSender)
{
	music m;
	m.effectStart("sound/effect_btn_click.mp3");
	Scene *pScene = OptionScene::scene();

	Director::getInstance()->replaceScene(pScene);
}

void mainScene::menuHelpCallback(Object* pSender)
{// pineoc's help 구현. HelpScene클래스 사용.
	music m;
	m.effectStart("sound/effect_btn_click.mp3");
	Scene *pScene = HelpScene::createScene();

	Director::getInstance()->pushScene(pScene);

	/*
	CCScene* pScene = CCScene::create();
	HelpScene *pLayer = new HelpScene("main");
	pLayer->autorelease();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->pushScene(pScene);
	*/
	
}

void mainScene::menuStartCallback(Object* pSender)
{
	music m;
	m.effectStart("sound/effect_btn_click.mp3");
	Scene *pScene = BuildingScene::createScene();

	Director::getInstance()->replaceScene(pScene);
}

void mainScene::menuDevCallback(Object* pSender)
{
	music m;
	m.effectStart("sound/effect_btn_click.mp3");
	Scene *pScene = MakerInfoScene::createScene();

	Director::getInstance()->pushScene(pScene);
}
