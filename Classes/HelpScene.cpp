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
	Scene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = Scene::create();

        // 'layer' is an autorelease object
		HelpScene *layer = HelpScene::create();

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool HelpScene::init()
{
	bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        if ( !LayerColor::initWithColor(Color4B(28, 39, 43, 255)))
        {
            return false;
        }

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		Size size = Director::getInstance()->getWinSize();
		
		/*
		±âÁ¸ ¹è°æÈ­¸é ¼³Á¤
		*/
		Sprite* phelpMainScene = Sprite::create("help01.png");
        CC_BREAK_IF(! phelpMainScene);

		//phelpMainScene->setScale(0.85);
		phelpMainScene->setPosition(Vec2(240, 1200));

		Sprite* phelpMainScene2 = Sprite::create("help02.png");
        CC_BREAK_IF(! phelpMainScene2);

		//phelpMainScene2->setScale(0.85);
		phelpMainScene2->setPosition(Vec2(240, 400));

		LayerColor *layer = LayerColor::create(ccc4(255, 255, 255, 255));
		layer->setAnchorPoint(Vec2());
		layer->setPosition(Vec2());
		layer->setContentSize(Size(480, 1600));

		layer->addChild(phelpMainScene);
		layer->addChild(phelpMainScene2);

		scrollView = ScrollView::create();
		scrollView->retain();
        scrollView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
        scrollView->setInnerContainerSize(layer->getContentSize());
		scrollView->setContentSize(layer->getContentSize());
		scrollView->setPosition(Vec2());

		this->addChild(scrollView);

		MenuItemImage *pCloseHelpScene = MenuItemImage::create(
            "btn_goBack.png",
            "btn_goBack_n.png",
            this,
			menu_selector(HelpScene::menu_closeHelpScene));
        CC_BREAK_IF(! pCloseHelpScene);

        // Place the menu item bottom-right conner.
		pCloseHelpScene->setPosition(ccp(size.width / 1.25 , size.height /14.28 ));
		
		CCMenu* pCloseHelpMenu = CCMenu::create(pCloseHelpScene,NULL);
		pCloseHelpMenu->setPosition(CCPointZero);
		this->addChild(pCloseHelpMenu,1);

        bRet = true;
    } while (0);

	return true;
}

void HelpScene::menu_closeHelpScene(CCObject* pSender)
{ // µµ¿ò¸»Ã¢À» ´ÝÀ½
	CCDirector::sharedDirector()->popScene();
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
