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
    if(!LayerColor::initWithColor(Color4B::WHITE))
    {
    	return false;
    }

	//������ ������
	winSize = Director::getInstance()->getVisibleSize();

	//Infoâ ���̾� �߰�
	pInfo = Sprite::create("img/devinfoScene_bg.png");
	pInfo->setPosition(Vec2(winSize.width/2,winSize.height/2));
	pInfo->setScale(winSize.width/pInfo->getContentSize().width);
	this->addChild(pInfo);

	//�ݱ��ư
	MenuItemImage *pClose = MenuItemImage::create(
		"img/btn_goBack.png","img/btn_goBack_n.png",
		this,menu_selector(MakerInfoScene::doClose));
	pClose->setPosition(Vec2(winSize.width / 1.35 , winSize.height /14.23));
	Menu* pMenu = Menu::create(pClose,NULL);
	pMenu->setPosition(Vec2());
	this->addChild(pMenu);

	return true;
}


void MakerInfoScene::doClose( Object* pSender )
{
	Director::getInstance()->popScene();
}
