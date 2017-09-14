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
#include "ui/CocosGUI.h"
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
	void goMain(Ref* pSender );	//메인으로
	void newGame(Ref* pSender );	//새게임
	void goHelp (Ref* pSender );	//도움말
	void doClose(Ref* pSender );	//이어하기
	
	void setStageIdx(int num); // set stage index 
	
	void menuPauseCallback (Ref* pSender);	//콜백
};

#endif
