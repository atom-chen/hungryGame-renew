/*
	빌딩선택창
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
        if(! Layer::init())
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


		//첫번째 건물버튼
        MenuItemImage *pBuilding_1 = MenuItemImage::create(
            "img/buildingSelect_btn_b1.png",
            "img/buildingSelect_btn_b1_n.png",
            this,
			menu_selector(BuildingScene::menuBuild1Callback));

        // Place the menu item bottom-right conner.
		pBuilding_1->setPosition(Vec2(size.width/3.33, size.height/1.53));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pMenu1 = Menu::create(pBuilding_1, NULL);
        pMenu1->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu1, 1);

		//두번째 건물버튼
        MenuItemImage *pBuilding_2 = MenuItemImage::create(
            "img/buildingSelect_btn_b2.png",
            "img/buildingSelect_btn_b2_n.png",
            this,
			menu_selector(BuildingScene::menuBuild2Callback));

        // Place the menu item bottom-right conner.
		pBuilding_2->setPosition(Vec2(size.width/1.42, size.height/1.53));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pMenu2 = Menu::create(pBuilding_2, NULL);
        pMenu2->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu2, 1);


		
        MenuItemImage *pBuilding_3 = MenuItemImage::create(
            "img/buildingSelect_btn_b3.png",
            "img/buildingSelect_btn_b3_n.png",
            this,
			menu_selector(BuildingScene::menuBuild3Callback));

        // Place the menu item bottom-right conner.
		pBuilding_3->setPosition(Vec2(size.width/3.33, size.height/3.33));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pMenu3 = Menu::create(pBuilding_3, NULL);
        pMenu3->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu3, 1);


		//네번째 건물버튼
        MenuItemImage *pBuilding_4 = MenuItemImage::create(
            "img/buildingSelect_btn_b4.png",
            "img/buildingSelect_btn_b4_n.png",
            this,
			menu_selector(BuildingScene::menuBuild4Callback));

        // Place the menu item bottom-right conner.
		pBuilding_4->setPosition(Vec2(size.width/1.42, size.height/3.33));

        Menu* pMenu4 = Menu::create(pBuilding_4, NULL);
        pMenu4->setPosition(Vec2());

        this->addChild(pMenu4, 1);


		//되돌아가기 버튼
        MenuItemImage *pGoBack = MenuItemImage::create(
            "img/btn_goBack.png",
            "img/btn_goBack_n.png",
            this,
			menu_selector(BuildingScene::menuGoBackCallback));

        // Place the menu item bottom-right conner.
		pGoBack->setPosition(Vec2(size.width/1.25, size.height/14.28));

        // Create a menu with the "close" menu item, it's an auto release object.
        Menu* pMenu5 = Menu::create(pGoBack, NULL);
        pMenu5->setPosition(Vec2());

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu5, 1);
        
    return true;
}

// 첫번째 빌딩
void BuildingScene::menuBuild1Callback(CCObject* pSender)
{
	music m;
	char buf[4];
	m.effectStart("sound/effect_btn_click.mp3");
	Scene *pScene = stageSelectScene::createScene();
	buildingNum = 10;
	sprintf(buf,"%d",buildingNum);
	CCString* popParam=CCString::create(buf);
	NotificationCenter::sharedNotificationCenter()->postNotification("BuildingNoti", popParam);
	
	Director::getInstance()->replaceScene(pScene);
}

//두번째 빌딩
void BuildingScene::menuBuild2Callback(Object* pSender)
{
	music m;
	char buf[4];
	m.effectStart("sound/tn_click.mp3");
	CCScene *pScene = stageSelectScene::createScene();
	buildingNum = 20;
	sprintf(buf,"%d",buildingNum);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("BuildingNoti", popParam);
	
	Director::getInstance()->replaceScene(pScene);
}

//세번째 빌딩
void BuildingScene::menuBuild3Callback(Object* pSender)
{
	music m;
	char buf[4];
	m.effectStart("sound/effect_btn_click.mp3");
	CCScene *pScene = stageSelectScene::createScene();
	buildingNum = 30;
	sprintf(buf,"%d",buildingNum);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("BuildingNoti", popParam);
	
	Director::getInstance()->replaceScene(pScene);
}

//네번째 빌딩
void BuildingScene::menuBuild4Callback(Object* pSender)
{
	music m;
	char buf[4];
	m.effectStart("sound/effect_btn_click.mp3");
	CCScene *pScene = stageSelectScene::createScene();
	buildingNum = 40;
	sprintf(buf,"%d",buildingNum);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("BuildingNoti", popParam);
	
	Director::getInstance()->replaceScene(pScene);
}

//되돌아가기
void BuildingScene::menuGoBackCallback(CCObject* pSender)
{
	music m;
	m.effectStart("sound/effect_btn_click.mp3");

	Scene *pScene = mainScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

