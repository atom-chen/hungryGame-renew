/**
* 2013 08 18
* Joung Daun
* GameScene
*/
#include "stageSelectScene.h"
#include "music.h"
#include "mainScene.h"
#include "gameScene.h"
#include "PauseGameScene.h"
#include "gameResultScene.h"
#include "userData.h"
using namespace cocos2d;

enum crashSomething { nothing, CrashWithWall, CrashWithFood, CrashWithItem};
enum DIRCTION { UP, DOWN, LEFT, RIGHT};
#define MOVEX 23.2
#define MOVEY 46.5


/*
* ** DESTRUCTURE
* ~gameScene()									destructure about gameScene class
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
gameScene::~gameScene()
{
	//delete foodSpriteArray;
	//delete foodFollowArray;
	this->onExit();
}
Scene* gameScene::createScene()
{
	Scene* scene = Scene::create();

	gameScene *layer = gameScene::create();

	scene->addChild(layer);

	return scene;
}



// on "init" you need to initialize your instance
/*
* ** FUNCTION
* bool init()									when scene made, this function is first called.
* Input											nothing
* Output										True
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun , eunji, jiyoon, pineoc
*/
bool gameScene::init()
{
    if(!LayerColor::initWithColor(Color4B::WHITE))
		return false;
	gStageidx = UserDefault::getInstance()->getIntegerForKey("curStage");
    foodSpriteArray.clear(); //food sprite array dynamic cast
    foodFollowArray.clear();
	result=" ";
	isSuper = false;
	

	//using stageidx for regame
	//set idx end. 
	//gStageidx = stageIDX;
    std::string map = StringUtils::format("map/%d.tmx", gStageidx);

	music m;
	m.effectStart("sound/effect_supermarket.mp3");

	Size size = Director::getInstance()->getWinSize();

	/* Set background img		: Daun */
	Sprite* bg = Sprite::create("img/game/game_bg.png");
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg,0);
    
    std::string stagenum = StringUtils::format("img/game/stageNum/%d.png",gStageidx-9);
	Sprite* stageNSprite = Sprite::create(stagenum);
	stageNSprite->setPosition(Vec2(size.width*0.32,size.height*0.93));
	this->addChild(stageNSprite,0);


	/* Set Tiled Map			: Daun, eunji*/
	Layer *tileLayer = Layer::create();
	this->addChild(tileLayer);

	tileMap = TMXTiledMap::create(map);
	tileMap->setPosition(MOVEX , MOVEY);
	if(tileMap->getLayer("wall"))
		backgroundLayer = tileMap->getLayer("wall");

	//metainfo에 준 타일레이어 이름은 Items이지만 벽표시 위한 빨간레이어임.
	// 추후 실제 아이템을 포함 할 수도 있음.
	if(tileMap->getLayer("Items"))
	{
		metainfo = tileMap->getLayer("Items");
		metainfo->setVisible(false);
	}
	tileLayer->addChild(tileMap);



	/* Make Character			: Daun */
	createCharacter();

	movingSpeed = 0.45;														// set initial character moving speed
	moveDirection = UP;													// set default character moving direction

	this->schedule(schedule_selector(gameScene::moveCharacter),movingSpeed);



	/* set touch enable			: Daun*/
	pDirector = Director::getInstance();

	/* make food				: Pineoc */
	
	this->createFood();
	foodcount = (int)foodSpriteArray.size();
	this->createFoodShelf();
	this->schedule(schedule_selector(gameScene::updateFoodSprite));
	this->schedule(schedule_selector(gameScene::check_counter));
	this->schedule(schedule_selector(gameScene::followCharacter));
	this->schedule(schedule_selector(gameScene::checkFollowFoodCollision));


	/* make obstacle			: eunji */
	isPause = false;

	if(tileMap->getObjectGroup("obstacle"))
	{
		TMXObjectGroup *obstacle = tileMap->getObjectGroup("obstacle");
		ValueMap obstaclePoint = obstacle->getObject("obstaclePoint");
        obstaclePoint.at("x");
        obX = obstaclePoint.at("x").asInt();
		obY = obstaclePoint.at("y").asInt();;

		obstaclePosition = Vec2(obX+MOVEX, obY+MOVEY);

		this->createObstacle();

		countNum = 0;
		checkObDirection = false; //false : 오른쪽 true : 왼쪽

		this->schedule(schedule_selector(gameScene::moveObstacleHeight), 1.0f); // 움직이는 장애물 구현
	}



	/* make gauge				: eunji */
	character_XP = 100;

	gaugeBar = Sprite::create("img/game/game_status_bar.png");
	gaugeBar->setPosition(Vec2(size.width*0.45, size.height*0.79));

	tileMap->addChild(gaugeBar,2);

	gaugeHeart = Sprite::create("img/game/game_heart.png");
	gaugeHeart->setPosition(Vec2(size.width - 30, size.height*0.79));

	tileMap->addChild(gaugeHeart,3);




	/* make pause btn			: jiyoon, daun */
	btnPause = Sprite::create("img/game/game_btn_pause.png");
	btnPause->setAnchorPoint(Vec2(0,0));

	pauseBtnPosition = Vec2(size.width*0.8, size.height*0.9);
	btnPause->setPosition(pauseBtnPosition);
	this->addChild(btnPause);


	/* Add notification			: jiyoon */
	NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(gameScene::doNotification),
		"notification", NULL);
	//"notification"이라는 메시지가 오면 해당 함수를 실행한다.



	/* Add Items				: jiyoon */
	//decide kind of item.
	srand(time(0));	//random
	int kindOfItem = 4;//rand()%4 + 1;	//range : 1~4
	item1 =NULL, item2 = NULL, item3 =NULL, item4=NULL;
	if(tileMap->getObjectGroup("items"))
	{
		TMXObjectGroup *items = tileMap->getObjectGroup("items");

		//select item decided before
		if (kindOfItem == 1)
		{
			//Add item1
			ValueMap item1 = items->getObject("item1");

			//Set item's position
			int temX = item1.at("x").asInt();
			int temY = item1.at("y").asInt();

			itemPosition = Vec2(temX+MOVEX,temY+MOVEY);
			this->createItem1();
		}
		else if (kindOfItem == 2)
		{
			//Add item2
			ValueMap item2 = items->getObject("item2");

			//Set item's position
			int temX = item2.at("x").asInt();
			int temY = item2.at("y").asInt();

			itemPosition = Vec2(temX+MOVEX,temY+MOVEY);
			this->createItem2();
		}
		else if (kindOfItem == 3)
		{
			//Add item3
			ValueMap item3 = items->getObject("item3");

			//Set item's position
			int temX = item3.at("x").asInt();
			int temY = item3.at("y").asInt();

			itemPosition = Vec2(temX+MOVEX,temY+MOVEY);
			this->createItem3();

		}
		else if (kindOfItem == 4)
		{
			//Add item4
			ValueMap item4 = items->getObject("item4");

			//Set item's position
			int temX = item4.at("x").asInt();
			int temY = item4.at("y").asInt();

			itemPosition = Vec2(temX+MOVEX,temY+MOVEY);
			this->createItem4();
		}
	}
	this->schedule(schedule_selector(gameScene::check_item));
	return true;
}
/*
* ** FUNCTION
* Vec2oint tileCoorPosition(Vec2oint)				??????????????
* Input											position 
* Output										???????
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/


Vec2 gameScene::tileCoorPosition(Vec2 position)
{
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return Vec2(x, y);
}

/*
* ** FUNCTION
* void createObstacle()							create Obstacle
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/
void gameScene::createObstacle()
{
	Texture2D *obTexture = TextureCache::sharedTextureCache()->addImage("map/meat.png");

	obstacle = Sprite::createWithTexture(obTexture,Rect(0, 0, 60, 60)); // 맵에 맞춰 숫자 바꿔야함
	obstacle->setPosition(obstaclePosition);
	obstacle->setAnchorPoint(Vec2(0,0));
	this->addChild(obstacle);
}


/*
* ** FUNCTION
* void onEnter()								called when enter this scene.
*												if this function not exist, touch event can not accepted.
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun
*/
void gameScene::onEnter()
{
	Layer::onEnter();
}

/*
* ** FUNCTION
* void moveCharacter(float)						make schedule function about moving character to it's own direction.
* Input											float dt for schedule.
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun, eunji, pineoc
*/
void gameScene::moveCharacter(float dt)
{
	Vec2 playerPos = character->getPosition();
	Vec2 originalplayerPos = character->getPosition();
	int checkCrash = nothing;



	/*  check collision food and character						: Pineoc*/
	beforeMoveCharPoint[0] = character->getPosition();
	foodFollowCnt=1;
    for(int i=0;i<foodSpriteArray.size();i++)
	{
        Sprite* foodFollow = foodSpriteArray.at(i);
		beforeMoveCharPoint[foodFollowCnt] = foodFollow->getPosition();
		foodFollowCnt++;
	}

	if(checkCrash == nothing)
	{
		if      (moveDirection == UP)	 {	playerPos.y += tileMap->getTileSize().height;	}
		else if (moveDirection == DOWN)  {	playerPos.y -= tileMap->getTileSize().height;	}
		else if (moveDirection == LEFT)	 {	playerPos.x -= tileMap->getTileSize().width;	}
		else if (moveDirection == RIGHT) {	playerPos.x += tileMap->getTileSize().width;	}
		else{}
	}

	/* check if character crash with wall						: eunji, Daun */

	if (playerPos.x <= (tileMap->getMapSize().width * tileMap->getTileSize().width)
		&& playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height)
		&& playerPos.y >= 0
		&& playerPos.x >= 0 )
	{
		// 캐릭터가 이동할 위치가 맵 안인경우 벽에 충돌햇는지를 검사합니다 By Daun
		Vec2 tileCoord = this->tileCoorPosition(playerPos);

		int tileGidforWall = this->metainfo->getTileGIDAt(tileCoord);
        

		if(tileGidforWall)
		{
			Value properties = tileMap->getPropertiesForGID(tileGidforWall);

			if(!properties.isNull())
			{
                std::string wall = properties.asString();

				if(wall.length() > 0 && (wall.compare("YES") == 0))
				{
					character->setPosition(playerPos);
					checkCrash = CrashWithWall;
					moveDirection = (moveDirection + 2 ) % 4;
				}
			}
		}
	}
	else
	{
		// 캐릭터가 이동할 위치가 맵 밖이므로 벽에 충돌한 것과 마찬가지입니다.
		checkCrash = CrashWithWall;
		moveDirection = (moveDirection + 2 ) % 4;
	}



	/* when character crash with wall							: eunji, Daun, jiyun */
	if(checkCrash == CrashWithWall)
	{
		music m;
		m.effectStart("sound/effect_crash_wall.mp3");

		Size size = Director::getInstance()->getWinSize();
		if(isSuper==false)
		{
			// 벽과 충돌한 경우 해야할 일
			character->setPosition(originalplayerPos);							// By Daun.. 충돌인 경우 원래 위치로 계쏙 유지
			character_XP -= 10;

			int gaugeSize_part = 441/10;										// 게이지바 사이즈의 10퍼센트 길이
			int gaugeNum = (gaugeSize_part * ((100 - character_XP) / 10));


			decreaseGaugeBar(gaugeNum);
		}

	}
	else
	{
		if (playerPos.x <= (tileMap->getMapSize().width * tileMap->getTileSize().width)
			&& playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height)
			&& playerPos.y >= 0
			&& playerPos.x >= 0 )
		{
			character->setPosition( playerPos );							// 캐릭터의 새로운 위치 지정
		}
	}

}


/*
* ** FUNCTION
* void createCharacter()						make character on map
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun
*/
void gameScene::createCharacter()
{

	Size size = Director::getInstance()->getWinSize();


	TMXObjectGroup *object = tileMap->getObjectGroup("object");
	ValueMap spawnPoint = object->getObject("character");

	int x = spawnPoint.at("x").asInt() + 1;
	int y = spawnPoint.at("y").asInt() + 1;

	Vec2 characterPosition = Vec2(x+MOVEX,y+MOVEY);

	// make charcter show in map
	Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("img/character/character.png");

	Animation *animation = Animation::create();
	animation->setDelayPerUnit(0.1);


	character = Sprite::createWithTexture(texture, Rect(0,0,35,48));
	character->setAnchorPoint(Vec2(0,0));

	// character->setScale(0.05);
	character->setPosition(characterPosition);
	//character->setFlipX(true); // X축 기준으로 반전
	//character->setFlipY(true);	// Y축 기준으로 반전

	animate = Animate::create(animation);
	rep = RepeatForever::create(animate);
	character->runAction(rep);

	this->addChild(character,60);
}


/*
* ** FUNCTION
* void createFood()								create food
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::createFood()
{
    //collision correct, duplication correct
	//char* inputdata = NULL;
	//CCString *a=NULL;
	const char* foodarr[10]={"food1","food2","food3","food4","food5","food6","food7","food8","food9","food10"};
	//for sprite food

	//create counter
	TMXObjectGroup *counterGroup = tileMap->getObjectGroup("endPoint");
	ValueMap _counterPoint = counterGroup->getObject("counter");
	int counterX = _counterPoint.at("x").asInt();
	int counterY = _counterPoint.at("y").asInt();
	counterPoint = Vec2(counterX+MOVEX,counterY+MOVEY);
	this->createCounter();
	//create counter end


	//
    std::string food_arr = StringUtils::format("img/food/%d_f.png",gStageidx);
    Texture2D *foodTexture = Director::getInstance()->getTextureCache()->addImage(food_arr);
	foods = tileMap->getObjectGroup("foods");

	for(int i = 0 ; i < 10; i++)
	{
		ValueMap dfoodpoint = foods->getObject(foodarr[i]);
        if(dfoodpoint.size()<1)
			break;
		//if does not have food, break
		int foodX = dfoodpoint.at("x").asInt();
		int foodY = dfoodpoint.at("y").asInt();
		Vec2 foodpoint = Vec2(foodX+MOVEX,foodY+MOVEY);
		Sprite* food = Sprite::createWithTexture(foodTexture,Rect(100*(i%5),100*(i/5),100,100));
		food->setPosition(foodpoint);
		food->setScale(0.48);
		food->setTag(i+1);
		food->setAnchorPoint(Vec2(0,0));
		//foodSpriteArray->addObject(food);
        foodSpriteArray.pushBack(food);
		this->addChild(food);
	}
    log("foodSpriteArray check");
}


/*
* ** FUNCTION
* bool checkDup(Sprite*)						check duplication function
* Input											Food we need to check duplication		???
* Output										scene
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
bool gameScene::checkDup(Sprite* checkfood)
{// if dup, return false
	//it can be useful another object.
	int tileGid = 1;//backgroundLayer->tileGIDAt(location);
	//int foodarrCount = foodSpriteArray->count();
	Rect checkfoodbounding = checkfood->getBoundingBox();
	for(int i=0;i<foodcount;i++)
	{//check the all food object
		Sprite* check = (Sprite*)foodSpriteArray.at(i);
		Rect checkbounding = check->getBoundingBox();
		if(checkfoodbounding.intersectsRect(checkbounding))
		{
			return false;
		}
	}
	if(tileGid == 0)
		return true;
	else
		return false;
	//return true;
}


/*
* ** FUNCTION
* void updateFoodSprte(float)					when character eat food, make food dissappear.
* Input											float for schedule.
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::updateFoodSprite(float dt)
{
    Vector<Sprite*> foodToDelete;
	Size size = Director::getInstance()->getVisibleSize();
	//CCARRAY_FOREACH(foodSpriteArray, foodobject)
    for(int i=0;i<foodcount;i++)
	{
		Rect characterRect = Rect(character->getPosition().x - (character->getContentSize().width/2),
			character->getPosition().y -(character->getContentSize().height/2),
			character->getContentSize().width,
			character->getContentSize().height);
		Sprite* foodSprite = foodSpriteArray.at(i);
		Rect foodRect = Rect(foodSprite->getPosition().x - (foodSprite->getContentSize().width/2*foodSprite->getScale()),
			foodSprite->getPosition().y -(foodSprite->getContentSize().height/2*foodSprite->getScale()),
			foodSprite->getContentSize().width*foodSprite->getScale(),
			foodSprite->getContentSize().height*foodSprite->getScale());
		if(characterRect.intersectsRect(foodRect))
        {
            foodToDelete.pushBack(foodSprite);
            //foodToDelete->addObject(foodSprite);
			//foodFollowArray->addObject(foodSprite);//add foods for following character
			//foodSpriteArray->removeObject(foodobject);
		}
	}
	//CCARRAY_FOREACH(foodToDelete,foodobject)
    for(int i=0;i<foodToDelete.size();i++)
	{
        Sprite* delfood = foodToDelete.at(i);
        foodFollowArray.eraseObject(delfood);
		foodSpriteArray.eraseObject(delfood);
	}
	foodToDelete.clear();
}
/*
* ** FUNCTION
* void checkFollowFoodCollision(float)			check if charcter crash with food
* Input											float for schedule
* Output										scene
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::checkFollowFoodCollision(float dt)
{
	Object* foodobject = NULL;
	Size size = Director::getInstance()->getWinSize();
	//CCARRAY_FOREACH(foodFollowArray,foodobject)
    for(int i=0;i<foodFollowArray.size();i++)
	{
		Rect characterRect = Rect(character->getPosition().x - (character->getContentSize().width/2),
			character->getPosition().y -(character->getContentSize().height/2),
			character->getContentSize().width,
			character->getContentSize().height);
		Sprite* foodSprite = dynamic_cast<Sprite*>(foodobject);
		Rect foodRect = Rect(foodSprite->getPosition().x - (foodSprite->getContentSize().width/2*foodSprite->getScale()),
			foodSprite->getPosition().y -(foodSprite->getContentSize().height/2*foodSprite->getScale()),
			foodSprite->getContentSize().width*foodSprite->getScale()-20,
			foodSprite->getContentSize().height*foodSprite->getScale()-20);
		if(characterRect.intersectsRect(foodRect) 
			&& foodFollowArray.at(0)!=foodobject
			&& foodFollowArray.at(1)!=foodobject
			&& foodFollowArray.at(2)!=foodobject)
		{
			this->decreaseGaugeBar(10);
		}

	}
}
/*
* ** FUNCTION
* void followCharacter(float dt)				make food follow the character.
* Input											float for schedule
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::followCharacter(float dt)
{
	Vec2 tmp1=beforeMoveCharPoint[0];
	Vec2 tmp2;

	for(int i=1;i<foodFollowArray.size()+1;i++)
	{
		Sprite* foodf = dynamic_cast<Sprite*>(foodFollowArray.at(i-1));
		foodf->setPosition(tmp1);
		tmp2=beforeMoveCharPoint[i];
		tmp1=tmp2;	
	}
}
/*
* ** FUNCTION
* void check_counter(float dt)					check if character come to counter
* Input											float for schedule
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::check_counter(float dt)
{// check counter if crash with character and counter
	Rect characterRect = Rect(character->getPosition().x - (character->getContentSize().width/2),
		character->getPosition().y -(character->getContentSize().height/2),
		character->getContentSize().width,
		character->getContentSize().height);
	Rect counterRect = Rect(counter->getPosition().x - (counter->getContentSize().width/2),
		counter->getPosition().y -(counter->getContentSize().height/2),
		counter->getContentSize().width,
		counter->getContentSize().height);
	if(characterRect.intersectsRect(counterRect))
	{// call gameResultScene
		this->go_endResultScene(1);
	}
}

/*
* ** FUNCTION
* void createFoodShelf()						make Sprite to eat food.
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::createFoodShelf()
{// have to : add food count
	Size size = Director::getInstance()->getWinSize();
    std::string food_arr = StringUtils::format("img/food/%d_f.png",gStageidx);
    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage(food_arr);
	for(int i=0;i<7;i++)
	{
		Sprite* foodsprite = Sprite::createWithTexture(texture,Rect(100*(i%5),100*(i/5),100,100));
		Vec2 position = Vec2((size.width*0.12*(i+1)),size.height*0.73);
		foodsprite->setAnchorPoint(Vec2(0,0));
		foodsprite->setPosition(position);
		foodsprite->setScale(0.5);
		this->addChild(foodsprite);
	}
}



/*
* ** FUNCTION
* void createCounter()							make counter
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::createCounter()
{
	Texture2D *counterTexture = Director::getInstance()->getTextureCache()->addImage("map/counter.png");
	Sprite* _counter = Sprite::createWithTexture(counterTexture,Rect(0, 0,60,60));
	_counter->setPosition(counterPoint);
	_counter->setAnchorPoint(Vec2(0,0));
	counter = _counter;
	this->addChild(counter);
}

/*
* ** FUNCTION
* void go_endResultScene()						collision with character, go to gameResultScene
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::go_endResultScene(int chk)
{
	if(chk==1)
		this->checkFoodToEnd();
	else
		result=" ";
	Scene *pScene = Scene::create();
	gameResultScene *layer = new gameResultScene(result,gStageidx,foodcount);
	layer->autorelease();
	pScene->addChild(layer);
	Director::getInstance()->replaceScene(pScene);

}
/*
* ** FUNCTION
* void checkFoodToEnd()							make string about what character eat.
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::checkFoodToEnd()
{//string result = ?
    std::string c;
	int count = foodFollowArray.size();
	for(int i=0;i<count;i++)
	{
		Sprite* a = ((Sprite*)foodFollowArray.at(i));
        c = StringUtils::format("%d", a->getTag());
        result.append((std::string)c+" ");
	}
}

/*
* ** FUNCTION
* void goMainScene()							go to MainScene
* Input											nothing
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											Pineoc
*/
void gameScene::goMainScene()
{
	this->onExit();
	Scene *pScene = mainScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}
void gameScene::goRegame(int stage)
{
	Scene *pScene = gameScene::createScene();

	Director::getInstance()->replaceScene(pScene);
}
/*
* ** FUNCTION
* void doPop(CCObject*)							pop the pause scene
* Input											????
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::doPop(Object* pSender)
{
	//Director::sharedDirector()->getTouchDispatcher()->removeDelegate(this);		//set touch enable
    UserDefault::getInstance()->setIntegerForKey("curStage",gStageidx);
    UserDefault::getInstance()->flush();
	Scene* pScene=PauseGameScene::createScene();
	this->addChild(pScene,2000,2000);

}
/*
* ** FUNCTION
* void doNotification(CCObject *)				get notification		????
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::doNotification(Object *obj)
{
	//노티피케이션 받기
    String* pParam=(String*)obj;
	int flag = pParam->intValue();
	if(flag==1)
	{
		Director::getInstance()->resume();														//화면 재시작
		//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);		// set touch able
	}
	else if(flag==2)
	{
		Director::getInstance()->resume();
		//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		this->goMainScene();
	}
	else if(flag>=10 && flag<=48)
	{
		Director::getInstance()->resume();
		//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		this->goRegame(flag);
	}
	else
	{	
		//Array* childs = this->getChildren();
		Director::getInstance()->pause();													//화면 정지
		//Director::getInstance()->getTouchDispatcher()->removeDelegate(PauseMenu);			//메뉴버튼 비활성
	}

}

void gameScene::onExit()
{
	Layer::onExit();
	NotificationCenter::sharedNotificationCenter()->removeObserver(this, "notification");
}

/*
* ** FUNCTION
* void createItem1()							create item 1
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem1()
{
	Texture2D *itemTexture = Director::getInstance()->getTextureCache()->addImage("img/item1.png");

	Sprite* item = Sprite::createWithTexture(itemTexture,Rect(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(Vec2(0,0));
	item1 = item;
	this->addChild(item1);
}

/*
* ** FUNCTION
* void createItem2()							create item 2
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem2()
{
	Texture2D *itemTexture = Director::getInstance()->getTextureCache()->addImage("img/item2.png");

	Sprite* item = Sprite::createWithTexture(itemTexture,Rect(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(Vec2(0,0));
	item2 = item;
	this->addChild(item2);
}

/*
* ** FUNCTION
* void createItem3()							create item 3
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem3()
{
	Texture2D *itemTexture = Director::getInstance()->getTextureCache()->addImage("img/item3.png");

	Sprite* item = Sprite::createWithTexture(itemTexture,Rect(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(Vec2(0,0));
	item3 = item;
	this->addChild(item3);
}

/*
* ** FUNCTION
* void createItem4()							create item 4
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem4()
{
	Texture2D *itemTexture = Director::getInstance()->getTextureCache()->addImage("img/item4.png");

	Sprite* item = Sprite::createWithTexture(itemTexture,Rect(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(Vec2(0,0));
	item4 = item;
	this->addChild(item4);
}
/*
* ** FUNCTION
* void check_item(float dt)						check if character eat item or not.
* Input											float for schedule
* Output										scene
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::check_item(float dt)
{
	//check collision - item, character
	Rect characterRect = Rect(character->getPosition().x - (character->getContentSize().width/2),
		character->getPosition().y - (character->getContentSize().height/2),
		character->getContentSize().width, character->getContentSize().height);

	Rect item1Rect;
	Rect item2Rect;
	Rect item3Rect;
	Rect item4Rect;
	if(item1 !=NULL)
	{
		item1Rect = Rect(item1->getPosition().x - (item1->getContentSize().width/2),
			item1->getPosition().y - (item1->getContentSize().height/2),
			item1->getContentSize().width, item1->getContentSize().height);
	}
	if(item2 !=NULL)
	{
		item2Rect = Rect(item2->getPosition().x - (item2->getContentSize().width/2),
			item2->getPosition().y - (item2->getContentSize().height/2),
			item2->getContentSize().width, item2->getContentSize().height);
	}
	if(item3 !=NULL)
	{
		item3Rect = Rect(item3->getPosition().x - (item3->getContentSize().width/2),
			item3->getPosition().y - (item3->getContentSize().height/2),
			item3->getContentSize().width, item3->getContentSize().height);
	}
	if(item4 !=NULL)
	{
		item4Rect = Rect(item4->getPosition().x - (item4->getContentSize().width/2),
			item4->getPosition().y - (item4->getContentSize().height/2),
			item4->getContentSize().width, item4->getContentSize().height);
	}

	if(characterRect.intersectsRect(item1Rect))
	{
		//item effect - gauge up 10%
		character_XP += 10;

		ActionInterval* gaugeUp = MoveBy::create(1,Vec2(44.1,0));
		//move by current position. +44.1(10% of the bar)
		gaugeHeart->runAction(gaugeUp);
		this->removeChild(item1);
		item1=NULL;
	}
	if(characterRect.intersectsRect(item2Rect))
	{
		//slow down effect
		movingSpeed = 0.65;
		this->removeChild(item2);
		item2=NULL;
	}
	if(characterRect.intersectsRect(item3Rect))
	{
		//pause obstacle effect
		isPause = true;	//정지 활성화
		count = 0;	//초세기 초기화
		this->removeChild(item3);
		item3=NULL;
	}
	if(characterRect.intersectsRect(item4Rect))
	{
		//superwoman effect
		isSuper = true;	//무적 활성화
		count = 0;	//초세기 초기화
		this->schedule(schedule_selector(gameScene::countTime),1.0f);	//초세기 시작
		this->doParticle();
		this->removeChild(item4);
		item4=NULL;
	}
}

/*
* ** FUNCTION
* void doParticle
* Input											nothing
* Output										nothing
* Date											2013. 11. 24
* Latest										2013. 11. 24
* Made											jiyun
*/
void gameScene::doParticle()
{
	ParticleSystem* super = ParticleFire::create();	//explosion particle
	super->retain();
	super->setTexture(Director::getInstance()->getTextureCache()->addImage("img/fire.png"));
	if(super != NULL)
	{
		//get current position of heart
		float X = gaugeHeart->getPositionX();
		float Y = gaugeHeart->getPositionY();
		
		super->setScale(1.0);	//scale
		super->setDuration(5.0);	//5sec
		super->setPosition(X,Y);	//heart
		this->addChild(super);
	}
}

/*
* ** FUNCTION
* void stopObstacle
* Input											nothing
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											jiyun
*/
void gameScene::stopObstacle()
{
	Director::getInstance()->getScheduler()->pauseTarget(obstacle);
	this->schedule(schedule_selector(gameScene::countTime),1.0f);
}

/*
* ** FUNCTION
* void countTime
* Input											nothing
* Output										nothing
* Date											2013. 11. 22
* Latest										2013. 11. 22
* Made											jiyun
*/
void gameScene::countTime(float d)
{
	if(count == 5)
	{
		if(isPause == true)
		{	resumeObstacle();	}
		if(isSuper == true)
		{  isSuper = false;	}
	}
	else
	{	count++;	}
}


/*
* ** FUNCTION
* void resumObstacle
* Input											nothing
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											jiyun
*/
void gameScene::resumeObstacle()
{
	isPause = false;
	Director::getInstance()->getScheduler()->resumeTarget(obstacle);
}

//--------------jiyoon end-----------------------------------------

//------------- eunji move obstacle -------------------------//
/*
* ** FUNCTION
* void moveObstacle(float dt)					make moving obstacle move
* Input											float for schedule
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											eunji
* Add											jiyun

*/
void gameScene::moveObstacleWidth(float dt)
{
	if(!isPause)
	{
		checkObDirection = !(checkObDirection);

		ActionInterval* moveRight = MoveBy::create(1, Vec2(60, 0));
		ActionInterval* moveLeft = MoveBy::create(1, Vec2(-60, 0));

		if     (checkObDirection == true)  {	obstacle->runAction(moveRight);}
		else if(checkObDirection == false) {	obstacle->runAction(moveLeft); }
	}

	else
	{
		stopObstacle();
	}
}

void gameScene::moveObstacleHeight(float dt)
{
	if(!isPause)
	{
		checkObDirection = !(checkObDirection);

		ActionInterval* moveRight = MoveBy::create(1, Vec2(0, 60));
		ActionInterval* moveLeft = MoveBy::create(1, Vec2(0, -60));

		if     (checkObDirection == true)  {	obstacle->runAction(moveRight);}
		else if(checkObDirection == false) {	obstacle->runAction(moveLeft); }
	}

	else
	{
		stopObstacle();
	}
}
/*
* ** FUNCTION
* void doActionMovingObstacleRight(CCObject*)	Make moving obstacle go to right side
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/

void gameScene::doActionMovingObstacleRight(Object* pSender)
{
	ActionInterval* moveRight = MoveBy::create(2, Vec2(200, 0));

	obstacle->runAction(moveRight);

}
/*
* ** FUNCTION
* void doActionMovingObstacleLeft(CCObject*)	Make moving obstacle go to left side
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/
void gameScene::doActionMovingObstacleLeft(Object* pSender)
{
	ActionInterval* moveLeft = MoveBy::create(2, Vec2(-80, 0));

	obstacle->runAction(moveLeft);
}
/*
* ** FUNCTION
* void doActionMovingObstaclReverse(CCObject*)	Make moving obstacle do action reversely
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/
void gameScene::doActionMovingObstacleReverse(Object* pSender)
{
	ActionInterval* moveRight = MoveBy::create(2, Vec2(80, 0));
	ActionInterval* moveReverse = moveRight->reverse();

	obstacle->runAction(moveReverse);
}

/*
* ** FUNCTION
* void doActionMovingObstaclReverse(CCObject*)	Dcrease Gauge bar 
* Input											int num
* Output										nothing
* Date											2013. 10. 05
* Latest										2013. 10. 05
* Made											eunji
*/

void gameScene::decreaseGaugeBar(int num)
{
	//x = 20 은 초기상태(에너지가 0인 상태)
	Size size = Director::getInstance()->getWinSize();

	if( character_XP > 0 )
	{
		gaugeHeart->setPositionX(size.width - (20 + num));		// num 값 만큼 감소시킴.	
	}

	else
	{
		//게임을 끝낸다
		gaugeHeart->setPositionX(20);
		this->go_endResultScene(0);
	}
}

/*
* ** FUNCTION
* void doActionMovingObstaclReverse(CCObject*)	Increase Gauge bar 
* Input											int num
* Output										nothing
* Date											2013. 10. 05
* Latest										2013. 10. 05
* Made											eunji
*/

void gameScene::increaseGaugeBar(int num)
{
	//x = 20 은 초기상태(에너지가 0인 상태)
	Size size = Director::getInstance()->getWinSize();

	if( character_XP < (460 - num) )
	{
		gaugeHeart->setPositionX(size.width - (20 - num));		// num 값 만큼 증가시킴.	
	}

	else
	{
		//게임을 끝낸다
		gaugeHeart->setPositionX(460);
		this->go_endResultScene(0);
	}
}

