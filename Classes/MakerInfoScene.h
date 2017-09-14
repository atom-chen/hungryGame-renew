#ifndef _MakerInfoScene_H
#define _MakerInfoScene_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MakerInfoScene : public cocos2d::LayerColor
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

    void doClose(cocos2d::Ref* obj);

	CREATE_FUNC(MakerInfoScene);

	cocos2d::Sprite* pInfo;
	cocos2d::Size winSize;
};

#endif
