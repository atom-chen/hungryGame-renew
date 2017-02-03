#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
/*
* 2013 08 18
* Joung Daun
* Game Scene
*/
#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class gameScene : public cocos2d::LayerColor
{
public:
	//gameScene(int );
	~gameScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();
    
   
    // implement the "static node()" method manually
	CREATE_FUNC(gameScene);

	/*
	pineoc's function (general function)
	display point -> tile point function
	*/
	Vec2 tileCoorPosition(Vec2);
	void createObstacle(); // ��ֹ� ���� ����

	TMXLayer *					backgroundLayer;
	TMXLayer *					metainfo; //��������
	Vec2							originPos;

	Vec2							obstaclePosition;
	Sprite *						obstacle;
	TMXLayer *					wall;



	/* gauge										: eunji */
	Sprite *						gaugeBar;
	Sprite *						gaugeHeart;
	int								character_XP;

	/* ,moving obstacle								: eunji */
	int								countNum;							// ������ ��.
	int								obX, obY;
	bool checkObDirection;
	void doActionMovingObstacleRight(Object* pSender);
	void doActionMovingObstacleLeft(Object* pSender);
	void moveObstacleHeight(float);// ��ֹ� ������ ����
	void moveObstacleWidth(float);
	void doActionMovingObstacleReverse(Object* pSender);

	void decreaseGaugeBar(int num);
	void increaseGaugeBar(int num);


	


	/* tiled map									: Daun */
	TMXTiledMap *tileMap; // tileMap name to select stage

	/* character									: Daun */
	float								movingSpeed;						// ĳ������ �̵� �ӵ�
	int								moveDirection;						// ĳ���Ͱ� ���� �̵��ϰ� �ִ� ������ ������
	int								beforeMoveDirection;				// �̰� ������ ���� �浹�ΰ�� ���� ������ ������
	Sprite*						character;
	void moveCharacter(float);
	void createCharacter();

	/* touch										: Daun */
	//void ccTouchEnded(CCTouch *, CCEvent* );
	//bool ccTouchBegan(CCTouch *, CCEvent* );
	void onEnter();

	/* pause										: Daun */
	Vec2							pauseBtnPosition;					// �Ͻ����� ��ư�� ��ġ
	Sprite *						btnPause;							// �Ͻ����� �̹���

	/* etc											: Daun */
	int								checkCrash;							// ĳ������ �浹 ���� �Ǵ�
	Director*						pDirector;




	/*												: pineoc */
	TMXObjectGroup *				foods;							// group for foods object
	Array*						onCheckFoodDisplay;				// ���� ������ �Ծ����� �ȸԾ����� üũ�� �迭,	
	void createFood();												//food create item, (point, imageName)
	bool checkDup(Sprite*);										// check duplication about tile
	void updateFoodSprite(float dt);
	void followCharacter(float);
	void check_counter(float);
	void createCounter();
	void go_endResultScene(int);
	void createFoodShelf();
	void checkFoodToEnd();											// check food for ending
	void checkFollowFoodCollision(float);
	void goMainScene();
	void goRegame(int);
	void onExit();
	
	// array for check when character eat the food ingrediant
    cocos2d::Vector<Sprite*>						foodSpriteArray;				// array for save the food sprite
	cocos2d::Vector<Sprite*>						foodFollowArray;				// array for follow character
	int								foodcount;						// for food count
	int								foodFollowCnt;
	Vec2							beforeMoveCharPoint[10];
	Sprite*						counter;
	Vec2							counterPoint;

	//char*							map;
	std::string						result;
	int								gStageidx;





	/*												: jiyoon*/
	Menu*							PauseMenu;						// pause button menu
	Vec2							itemPosition;
	Sprite*						item1,
			*						item2, 
			*						item3, 
			*						item4;
	Animate*						animate;
	Action *						rep;
	
	void doPop(Object* pSender);									//creat popup
	void doNotification(Object *obj);
	
	void createItem1();
	void createItem2();
	void createItem3();
	void createItem4();
	
	void check_item(float dt);										//check collision between item and character

	bool isPause;													//status of movingObstacle
	bool isSuper;													//status of character
	int count;														//count setting
	void stopObstacle();											//pauseObstacle
	void resumeObstacle();											//resume Obstacle
	void countTime(float d);										//count 3sec
	void doParticle();												//Particle - start SuperMode
};

#endif  // __GAME_SCENE_H__
