//pineoc@naver.com
//HelpScene.cpp
//µµ¿ò¸»Ã¢ ±¸Çö

#include "HelpScene.h"

//HelpScene::HelpScene(std::string _helpType)
//{
//	helpType = _helpType;
//}

Scene* HelpScene::createScene()
{
	Scene * scene = Scene::create();

    // 'layer' is an autorelease object
    HelpScene *layer = HelpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool HelpScene::init()
{
        if ( !LayerColor::initWithColor(Color4B::WHITE))
        {
            return false;
        }

		Size size = Director::getInstance()->getWinSize();

		scrollView = ScrollView::create();
		scrollView->retain();
        scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        scrollView->setInnerContainerSize(Size(size.width, size.height*2));
		scrollView->setContentSize(size);
		scrollView->setPosition(Vec2());
		this->addChild(scrollView);
		
		Sprite* phelpMainScene = Sprite::create("img/help01.png");
		phelpMainScene->setAnchorPoint(Vec2(0.5, 1));
		phelpMainScene->setPosition(Vec2(size.width/2, scrollView->getInnerContainerSize().height));
		phelpMainScene->setScale(size.width/phelpMainScene->getContentSize().width);

		Sprite* phelpMainScene2 = Sprite::create("img/help02.png");
		phelpMainScene2->setAnchorPoint(Vec2(0.5, 0));
		phelpMainScene2->setPosition(Vec2(size.width/2, 0));
		phelpMainScene2->setScale(size.width/phelpMainScene2->getContentSize().width);

		scrollView->addChild(phelpMainScene);
		scrollView->addChild(phelpMainScene2);

		MenuItemImage *pCloseHelpScene = MenuItemImage::create(
            "img/btn_goBack.png",
            "img/btn_goBack_n.png",
            this,
			menu_selector(HelpScene::menu_closeHelpScene));

        // Place the menu item bottom-right conner.
		pCloseHelpScene->setPosition(Vec2(size.width / 1.25 , size.height /14.28 ));
		
		Menu* pCloseHelpMenu = Menu::create(pCloseHelpScene,NULL);
		pCloseHelpMenu->setPosition(Vec2());
		this->addChild(pCloseHelpMenu,1);

	return true;
}

void HelpScene::menu_closeHelpScene(Ref* pSender)
{
	Director::getInstance()->popScene();
	//push, pop SceneÀ» ÀÌ¿ëÇØ¼­ µÇµ¹¾Æ°¡±â ±¸Çö.
}

void HelpScene::onEnter()
{
	Layer::onEnter();
	//Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}
void HelpScene::onExit()
{
	Layer::onExit();
	//CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
