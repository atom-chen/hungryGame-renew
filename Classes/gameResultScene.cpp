#include "gameResultScene.h"
#include "gameEndScene.h"
#include <algorithm>

gameResultScene::gameResultScene(std::string _result,int _stageidx,int _count)
{
	result = _result;
	stageidx = _stageidx;
	count = _count;
	this->init();
}

bool gameResultScene::init()
{
	if(!LayerColor::initWithColor(Color4B::WHITE))
		return false;
	
	Size size = Director::getInstance()->getWinSize();

	Sprite* background = Sprite::create("img/endResult/end_bg.png");
	background->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(background,0);

	std::string stageNum = StringUtils::format("img/game/stageNum/%d.png",stageidx-9);
	Sprite* stageNSprite = Sprite::create(stageNum);
	stageNSprite->setPosition(Vec2(size.width*0.32,size.height*0.93));
	this->addChild(stageNSprite,0);

	MenuItemImage *btnEnd = MenuItemImage::create(
		"img/endResult/main_btn_endgame.png", "img/endResult/main_btn_endgame_n.png", this, menu_selector(gameResultScene::menu_goEndScene));

	btnEnd->setPosition(Vec2(size.width*0.8, size.height*0.1));
	btnEnd->setScale(0.8);
	Menu* endMenu = Menu::create(btnEnd, NULL);
    endMenu->setPosition(Vec2::ZERO);

	this->addChild(endMenu, 2);

	parser();

	this->make_foodSprite();
	return true;
}
/**
전달받은 string parsing
*/
void gameResultScene::parser()
{
	for(int i = 0; i < 10; i++){
		check_arr[i] = 0;
	}
	for(int i = 0; i < result.length(); i++){
		if(!(i%2)) {
			char* nowChar = &result.at(i);
			int tmp = atoi(nowChar);
			check_arr[tmp] = 1;
		}
	}
}

void gameResultScene::make_foodSprite()
{//make food sprite using array foodArrayForSprite
	int successCnt = 0;			//성공한 음식 갯수 저장하는곳
	double x=0.2;
	double y=0.65;// for sprite position
	Size winSize = Director::getInstance()->getVisibleSize();
	for(int i=0;i<10;i++)
	{		
		if(i==2 || i==4 || i== 6 || i == 8)
		{
			x=0.2;
			y=y-0.15;
		}
		else if(i==1 || i==3 || i==5 || i==7 || i==9)
		{	
			x=0.6;
		}
		
		/**
		Daun
		이미지 뿌리는 부분...
		**/

		Vec2 position = Vec2(winSize.width*x,winSize.height*y);
		std::string food_arr = StringUtils::format("img/food/%d_f.png",stageidx);
        Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(food_arr);
		Sprite* foodsprite = Sprite::createWithTexture(texture, Rect(100*(i%5),100*(i/5),100,100));

		foodsprite->setAnchorPoint(Vec2(0,0));
		foodsprite->setPosition(position);

		if(check_arr[i+1] == 1) {
			//빨간 동그라미 그리기
			Sprite* check = Sprite::create("img/endResult/end_redCircle.png");
			check->setPosition(position);
			check->setAnchorPoint(Vec2(0,0));
			this->addChild(check,2);
			successCnt++;
		}

		this->addChild(foodsprite,1);
	}

	if(count == successCnt) {
			/*******************************여기 조건문 고쳐야함.. 스테이지에 몇개 음식인지를 받아와서 하는걸로..*******/
			resultOfStage = 1;
		} else resultOfStage = 0;
}

void gameResultScene::menu_goEndScene(Ref* pSender)
{
	Scene *pScene = Scene::create();
	gameEndScene *layer = new gameEndScene(resultOfStage,stageidx);
	layer->autorelease();
	pScene->addChild(layer);
	Director::getInstance()->replaceScene(pScene);
}
