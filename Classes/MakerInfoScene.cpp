#include "MakerInfoScene.h"

using namespace cocos2d;

Scene* MakerInfoScene::createScene()
{
	Scene *scene = Scene::create();

	MakerInfoScene *layer = MakerInfoScene::create();

	scene->addChild(layer);

	return scene;
}

bool MakerInfoScene::init()
{
	bool bRet = false;
	do 
	{
        CC_BREAK_IF(!LayerColor::initWithColor(Color4B::WHITE));

		//������ ������
		winSize = Director::getInstance()->getWinSize();

		//Infoâ ���̾� �߰�
		pInfo = Sprite::create("devinfoScene_bg.png");
		CC_BREAK_IF(!pInfo);
		pInfo->setPosition(Vec2(winSize.width/2,winSize.height/2));
		this->addChild(pInfo);

		//�ݱ��ư
		MenuItemImage *pClose = MenuItemImage::create(
			"btn_goBack.png","btn_goBack_n.png",this,menu_selector(MakerInfoScene::doClose));
		CC_BREAK_IF(!pClose);
		pClose->setPosition(Vec2(winSize.width / 1.35 , winSize.height /14.23));
		Menu* pMenu = Menu::create(pClose,NULL);
		pMenu->setPosition(Vec2());
		this->addChild(pMenu);

		bRet = true;
	} while (0);
	return true;
}


void MakerInfoScene::doClose( Object* pSender )
{
	//������
	Director::getInstance()->popScene();
}
