/*
pineoc@naver.com // 이윤석
game End Scene 
get result for success Scene or fail Scene 
*/

#include "gameEndScene.h"
#include "gameScene.h"
#include "BuildingScene.h"


gameEndScene::gameEndScene(int _result,int _stageidx)
{
    if(!LayerColor::initWithColor(Color4B::WHITE))
		return ;
	result = _result;
	stageidx = _stageidx;

	Size size = Director::getInstance()->getWinSize();

    std::string stagenum = StringUtils::format("img/game/stageNum/%d.png",stageidx-9);
	Sprite* stageNSprite = Sprite::create(stagenum);
	stageNSprite->setPosition(Vec2(size.width*0.32,size.height*0.93));
	this->addChild(stageNSprite,0);

	Sprite* background = Sprite::create("img/end/endChk_bg.png");
	background->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(background,0);

    std::string food_arr = StringUtils::format("img/food/%d.png",stageidx);
	Sprite* foodImage = Sprite::create(food_arr); //by eunji
	foodImage->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(foodImage,1);

	/*
	use result, make menu button 
	*/
	if(result == 1) // success the game
	{// menu button : retry , next stage, back to select building(stage)
		//success image 
		Sprite *success = Sprite::create("img/end/endChk_success.png");
		success->setPosition(Vec2(size.width/2, size.height/2));
		this->addChild(success,2);

		//retry button
		MenuItemImage *pMenu_retry = MenuItemImage::create(
			"img/end/endChk_btn_again.png","img/end/endChk_btn_again_n.png",
			this,
			menu_selector(gameEndScene::menu_retry));

		//go to nextstage button
		MenuItemImage *pMenu_nextStage = MenuItemImage::create(
			"img/end/endChk_btn_next.png","img/end/endChk_btn_next_n.png",
			this,
			menu_selector(gameEndScene::menu_nextStage));

		//go to stageScene
		MenuItemImage *pMenu_backtoStageScene = MenuItemImage::create(
		"img/end/end_btn_StageScene.png","img/end/end_btn_StageScene_n.png",
		this,
		menu_selector(gameEndScene::menu_backtoStageScene));
		
		// Create a menu with the "close" menu item, it's an auto release object.
		Menu* pMenu_s = Menu::create(pMenu_retry,pMenu_nextStage,pMenu_backtoStageScene, NULL);
		pMenu_retry->setScale(0.8);
		pMenu_nextStage->setScale(0.8);

		pMenu_s->alignItemsHorizontally();
		pMenu_s->setPosition(Vec2(size.width/2,size.height*0.2));
		this->lastStageSet();
		//// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu_s, 2);

	}
	else // result == 0 , fail the game
	{//menu button : retry, back to select building(stage)

		Sprite *fail = Sprite::create("img/end/endChk_fail.png");
		fail->setPosition(Vec2(size.width/2, size.height/2));
		this->addChild(fail,2);


		MenuItemImage *pMenu_retry = MenuItemImage::create(
			"img/end/endChk_btn_again.png","img/end/endChk_btn_again_n.png",
			this,
			menu_selector(gameEndScene::menu_retry));
		MenuItemImage *pMenu_backtoStageScene = MenuItemImage::create(
			"img/end/end_btn_StageScene.png","img/end/end_btn_StageScene_n.png",
			this,
			menu_selector(gameEndScene::menu_backtoStageScene));
		pMenu_retry->setScale(0.8);
		pMenu_backtoStageScene->setScale(0.8);
		Menu* pMenu_f = Menu::create(pMenu_retry,pMenu_backtoStageScene,NULL);
		pMenu_f->alignItemsHorizontally();
		pMenu_f->setPosition(Vec2(size.width/2,size.height*0.2));

		this->addChild(pMenu_f,2);
	}

}
bool gameEndScene::init()
{
	return true;
}
void gameEndScene::menu_retry(Ref* pSender)
{
	
	//여기서 스테이지의 idx가져와서 다시 replace 하는 방식으로 가야할듯.
	Scene *pScene = gameScene::createScene();
	Director::getInstance()->replaceScene(pScene);

}
void gameEndScene::menu_nextStage(Ref* pSender)
{
	
	//스테이지의 idx를 가져와서 idx+1 하여 다음 스테이지를 가져오게끔 해야할 듯.
	
	if(stageidx == 18 || stageidx==28 || stageidx==38)
		UserDefault::getInstance()->setIntegerForKey("curStage",stageidx+2);
	else
		UserDefault::getInstance()->setIntegerForKey("curStage",stageidx+1);
	UserDefault::getInstance()->flush();
    
	Scene *pScene = gameScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}
void gameEndScene::menu_backtoStageScene(Ref* pSender)
{
	/*
	스테이지 선택하는 Scene으로 넘어감.
	back to selectstage Scene
	*/
	Scene *pScene = BuildingScene::createScene();

	Director::getInstance()->replaceScene(pScene);
}
void gameEndScene::lastStageSet()
{
	UserDefault::getInstance()->setIntegerForKey("lastStage",stageidx+1);
	UserDefault::getInstance()->flush();
}
