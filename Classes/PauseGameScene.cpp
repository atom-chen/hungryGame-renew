#include "PauseGameScene.h"
#include "mainScene.h"
#include "HelpScene.h"

using namespace cocos2d;

Scene* PauseGameScene::createScene()
{
	Scene* scene = Scene::create();

	PauseGameScene *layer = PauseGameScene::create();

	scene->addChild(layer);

	return scene;
}

bool PauseGameScene::init()
{
	if( !LayerColor::initWithColor(Color4B(0,0,0,0)))
	{ return false; }
	pStageidx=UserDefault::getInstance()->getIntegerForKey("curStage");


	String* popParam=String::create("0");
	__NotificationCenter::getInstance()->postNotification("notification", popParam);         //노티피케이션 보내기

	winSize=Director::getInstance()->getWinSize();

	Sprite *bg = Sprite::create("img/pause/pause_bg.png");
	bg->setScale(0.5);
	bg->setPosition(Vec2(winSize.width/2,winSize.height/2));
	this->addChild(bg,0);
	
	//메뉴추가
	MenuItemImage* pMain = MenuItemImage::create(
		"img/pause/pause_btn_goMain.png","img/pause/pause_btn_goMain_n.png", this, menu_selector(PauseGameScene::goMain));
	pMain->setScale(0.5);
	MenuItemImage* pHelp = MenuItemImage::create(
		"img/pause/pause_btn_help.png","img/pause/pause_btn_help_n.png",this,menu_selector(PauseGameScene::goHelp));
	pHelp->setScale(0.5);
	MenuItemImage* pGame = MenuItemImage::create(
		"img/pause/pause_btn_restart.png","img/pause/pause_btn_restart_n.png", this, menu_selector(PauseGameScene::newGame));
	pGame->setScale(0.5);
	MenuItemImage* pClose = MenuItemImage::create(
		"img/pause/pause_btn_continue.png","img/pause/pause_btn_continue.png", this, menu_selector(PauseGameScene::doClose));
	pClose->setScale(0.5);

	//메뉴생성
	Menu* pauseMenu=Menu::create(pMain, pGame, pHelp, pClose, NULL);
	pauseMenu->setPosition(Vec2(240, 450));
	pauseMenu->alignItemsVertically();
	this->addChild(pauseMenu,10);

	//backLayer추가
    backLayer=LayerColor::create(Color4B(0,0,0,0), winSize.width, winSize.height);
	backLayer->setAnchorPoint(Vec2());
	backLayer->setPosition(Vec2());
	this->addChild(backLayer);

	//popUpLayer추가
	popUpLayer=LayerColor::create(Color4B(0,0,0,0), 250,150);
	popUpLayer->setAnchorPoint(Vec2(0,0));
	popUpLayer->setPosition(Vec2((winSize.width-popUpLayer->getContentSize().width)/2,
				(winSize.height-popUpLayer->getContentSize().height)/2   )  );
	this->addChild(popUpLayer);

    return true;
}


void PauseGameScene::goMain(Ref* pSender )
{
	//처음 메인화면으로
	/*CCScene *pScene = Main::scene();

	Director::sharedDirector()->pushScene(pScene);*/
	String* popParam=String::create("2");
	__NotificationCenter::getInstance()->postNotification("notification", popParam);         //노티피케이션 보내기
	this->removeFromParentAndCleanup(true);
}

void PauseGameScene::goHelp( Ref* pSender )
{
	//도움말 화면으로
	Scene *pScene = HelpScene::createScene();

	Director::getInstance()->pushScene(pScene);
	
}

void PauseGameScene::newGame(Ref* pSender )
{
	//게임화면 초기화
    std::string a = StringUtils::format("%d", pStageidx);
	String* popParam=String::create(a);
	__NotificationCenter::getInstance()->postNotification("notification", popParam);         //노티피케이션 보내기
	this->removeFromParentAndCleanup(true);

}

void PauseGameScene::doClose(Ref* pSender)
{
	//팝업창 닫고 게임 이어하기
	String* popParam=String::create("1");
	__NotificationCenter::getInstance()->postNotification("notification", popParam);         //노티피케이션 보내기
	this->removeFromParentAndCleanup(true);		//팝업창 제거

}

void PauseGameScene::setStageIdx(int num)
{
	pStageidx = num;
}
