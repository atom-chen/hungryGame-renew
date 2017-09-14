/*���� - ���� �� �Ͻ����� â
���� ���� �Ͻ�����
��������
������
����
�̾��ϱ�*/
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

	//�޴� 4����
	void goMain(Ref* pSender );	//��������
	void newGame(Ref* pSender );	//������
	void goHelp (Ref* pSender );	//����
	void doClose(Ref* pSender );	//�̾��ϱ�
	
	void setStageIdx(int num); // set stage index 
	
	void menuPauseCallback (Ref* pSender);	//�ݹ�
};

#endif
