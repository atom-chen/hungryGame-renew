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
    Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		stageSelectScene *layer = stageSelectScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool stageSelectScene::init()
{
        if(! Layer::init())
        {
        	return false;
        }

		Size size = Director::getInstance()->getWinSize();
		//sStageNum = 0;

		if(!UserDefault::getInstance()->getIntegerForKey("lastStage"))
		{
			UserDefault::getInstance()->setIntegerForKey("lastStage",10);
			UserDefault::getInstance()->flush();
		}

		//배경 이미지 생성
		Sprite* pStageBg = Sprite::create("img/stageSelect/stage_bg.png");
        pStageBg->setScale(size.width/pStageBg->getContentSize().width);

        // Place the sprite on the center of the screen
        pStageBg->setPosition(Vec2(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pStageBg, 0);

		//for stageNum of each building


		// 버튼 생성
		MenuItemImage *s1 = MenuItemImage::create(
			"img/stageSelect/stage_btn_1.png","img/stageSelect/stage_btn_1_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s1->setPosition(ccp(size.width * 0.2, size.height * 0.8));
		s1->setTag(0);
		
		MenuItemImage *s2 = MenuItemImage::create(
			"img/stageSelect/stage_btn_2.png","img/stageSelect/stage_btn_2_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s2->setPosition(ccp(size.width * 0.5, size.height * 0.8));
		s2->setTag(1);

		MenuItemImage *s3 = MenuItemImage::create(
			"img/stageSelect/stage_btn_3.png","img/stageSelect/stage_btn_3_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s3->setPosition(ccp(size.width * 0.8, size.height * 0.8));
		s3->setTag(2);

		CCMenuItemImage *s4 = CCMenuItemImage::create(
			"img/stageSelect/stage_btn_4.png","img/stageSelect/stage_btn_4_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s4->setPosition(ccp(size.width * 0.2, size.height * 0.62));
		s4->setTag(3);

		CCMenuItemImage *s5 = CCMenuItemImage::create(
			"img/stageSelect/stage_btn_5.png","img/stageSelect/stage_btn_5_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s5->setPosition(ccp(size.width * 0.5, size.height * 0.62));
		s5->setTag(4);

		MenuItemImage *s6 = MenuItemImage::create(
			"img/stageSelect/stage_btn_6.png","img/stageSelect/stage_btn_6_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s6->setPosition(ccp(size.width * 0.8, size.height * 0.62));
		s6->setTag(5);

		MenuItemImage *s7 = MenuItemImage::create(
			"img/stageSelect/stage_btn_7.png","img/stageSelect/stage_btn_7_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s7->setPosition(ccp(size.width * 0.2, size.height * 0.45));
		s7->setTag(6);

		MenuItemImage *s8 = MenuItemImage::create(
			"img/stageSelect/stage_btn_8.png","img/stageSelect/stage_btn_8_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s8->setPosition(ccp(size.width * 0.5, size.height * 0.45));
		s8->setTag(7);

		MenuItemImage *s9 = MenuItemImage::create(
			"img/stageSelect/stage_btn_9.png","img/stageSelect/stage_btn_9_n.png",this,menu_selector(stageSelectScene::stageMenu));

		s9->setPosition(ccp(size.width * 0.8, size.height * 0.45));
		s9->setTag(8);

		Menu *stageMenu = Menu::create(s1,s2,s3,s4,s5,s6,s7,s8,s9,NULL);
		stageMenu->setPosition(CCPointZero);

		this->addChild(stageMenu,1);


		//되돌아가기 버튼
        MenuItemImage *pGoBack = MenuItemImage::create(
            "img/btn_goBack.png",
            "img/btn_goBack_n.png",
            this,
			menu_selector(stageSelectScene::menuGoBackCallback));

        // Place the menu item bottom-right conner.
		pGoBack->setPosition(ccp(size.width/1.25, size.height/14.28));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pGoBackMenu = CCMenu::create(pGoBack, NULL);
        pGoBackMenu->setPosition(CCPointZero);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pGoBackMenu, 1);

		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(stageSelectScene::doMsgRecv),
			"BuildingNoti", NULL);

    return true;
}

void stageSelectScene::stageMenu(Object* pSender)
{
	music m;
	m.effectStart("sound/effect_btn_click.mp3");
	/***
	 여기에 게임 화면으로 전환하는거 들어감!!
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

//되돌아가기
void stageSelectScene::menuGoBackCallback(Object* pSender)
{
	Scene *pScene = BuildingScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void stageSelectScene::doMsgRecv(Object* obj)
{
	CCString* pParam = (CCString*)obj;
	int flag = pParam->intValue();
	if(flag>0)
		buildingNum = flag;
}
void stageSelectScene::onExit()
{
	Layer::onExit();
	NotificationCenter::sharedNotificationCenter()->removeObserver(this, "BuildingNoti");
}
void stageSelectScene::goStageScene()
{
	UserDefault::getInstance()->setIntegerForKey("curStage",sStageNum);
	UserDefault::getInstance()->flush();
	Scene* pScene = gameScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}
