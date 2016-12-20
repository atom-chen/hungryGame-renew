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
	void goMain( Object* pSender );	//��������
	void newGame( Object* pSender );	//������
	void goHelp ( Object* pSender );	//����
	void doClose( Object* pSender );	//�̾��ϱ�
	
	void setStageIdx(int num); // set stage index 
	
	void menuPauseCallback (Object* pSender);	//�ݹ�
};

#endif
