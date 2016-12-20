/*지윤 - 게임 중 일시정지 창
게임 도중 일시정지
메인으로
새게임
도움말
이어하기*/
#pragma once
#ifndef _PauseGameScene_
#define _PauseGameScene_

#include "cocos2d.h"
using namespace cocos2d;

class PauseGameScene : public LayerColor
{
public:
	virtual bool init();

	static Scene* createScene();
	CREATE_FUNC(PauseGameScene);
	Size winSize;

	LayerColor* backLayer;
	LayerColor* popUpLayer;

	int pStageidx;// integer for regame 

	//메뉴 4가지
	void goMain( Object* pSender );	//메인으로
	void newGame( Object* pSender );	//새게임
	void goHelp ( Object* pSender );	//도움말
	void doClose( Object* pSender );	//이어하기
	
	void setStageIdx(int num); // set stage index 
	
	void menuPauseCallback (Object* pSender);	//콜백
};

#endif
