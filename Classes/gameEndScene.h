/*
pineoc@naver.com // ¿Ã¿±ºÆ
game End Scene 
get result for success Scene or fail Scene 
*/


#pragma once
#include "cocos2d.h"
USING_NS_CC;
class gameEndScene : public LayerColor
{
public:
	gameEndScene(int,int);
	//~gameEndScene(void);

	virtual bool init();

	//static cocos2d::CCScene* scene();
	//CREATE_FUNC(gameEndScene);

	void menu_retry(Object*);// retry game
	void menu_backtoStageScene(Object*);//back to stageScene
	void menu_nextStage(Object*);//go to next stage
	void check_point_star(Object*);//check the point to make star
	void lastStageSet();

	int result; // game result, success or fail, success = 1, fail = 0
	int stageidx;// stage index
};
