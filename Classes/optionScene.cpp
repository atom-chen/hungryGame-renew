/*
* 2013 08 27
* option scene
* Daun
*/

#include "optionScene.h"


enum musicOnOffList{ bgOn, bgOff, effectOn, effectOff};
Scene* OptionScene::createScene()
{
	Scene * scene = Scene::create();

    // 'layer' is an autorelease object
    OptionScene *layer = OptionScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool OptionScene::init()
{
        if(!LayerColor::initWithColor(Color4B::WHITE))
        {
        	return false;
        }

		Size size = Director::getInstance()->getWinSize();
		
		Sprite* phelpMainScene = Sprite::create("img/option/option_bg.png");
		phelpMainScene->setPosition(Vec2(size.width/2,size.height/2));
		phelpMainScene->setScale(size.width/phelpMainScene->getContentSize().width);
		this->addChild(phelpMainScene,0);

		MenuItemImage *pBGON = MenuItemImage::create(
			"img/option/option_btn_on.png",
			"img/option/option_btn_on_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));

		pBGON->setPosition(Vec2(size.width * 0.6, size.height * 0.6));
		pBGON->setTag(bgOn);

		MenuItemImage *pBGOFF = MenuItemImage::create(
			"img/option/option_btn_off.png",
			"img/option/option_btn_off_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));

		pBGOFF->setPosition(Vec2(size.width * 0.8, size.height * 0.6));
		pBGOFF->setTag(bgOff);

		MenuItemImage *pEffectOn = MenuItemImage::create(
			"img/option/option_btn_on.png",
			"img/option/option_btn_on_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));

		pEffectOn->setPosition(Vec2(size.width * 0.6, size.height * 0.4));
		pEffectOn->setTag(effectOn);

		MenuItemImage *pEffectOff = MenuItemImage::create(
			"img/option/option_btn_off.png",
			"img/option/option_btn_off_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));

		pEffectOff->setPosition(Vec2(size.width * 0.8, size.height * 0.4));
		pEffectOff->setTag(effectOff);


		Menu *pONOFFMenu = Menu::create(pBGON, pBGOFF, pEffectOn, pEffectOff,NULL);
		pONOFFMenu->setPosition(Vec2());
		this->addChild(pONOFFMenu,1);

		/*
		Goback btn
		*/
		MenuItemImage *pCloseScene = MenuItemImage::create(
            "img/btn_goBack.png",
            "img/btn_goBack_n.png",
            this,
			menu_selector(OptionScene::goBackMenu));

        // Place the menu item bottom-right conner.
		pCloseScene->setPosition(Vec2(size.width / 1.25 , size.height /14.28 ));
		
		Menu* pCloseMenu = Menu::create(pCloseScene,NULL);
		pCloseMenu->setPosition(Vec2());
		this->addChild(pCloseMenu,1);

	return true;
}

void OptionScene::goBackMenu(Ref* pSender)
{ // 도움말창을 닫음
	Scene *pScene = mainScene::createScene();
	Director::getInstance()->replaceScene(pScene);
}

void OptionScene::OnOffMenu(Ref* pSender)
{
	// set fuction to on off buttons
	MenuItem *pGet = (MenuItem *)pSender;
	music m;
	switch(pGet->getTag())
	{
	case bgOn:
		userData::sharedInstance()->setBGM(true);
		m.bgStart("temp");
		break;
	case bgOff:
		userData::sharedInstance()->setBGM(false);
		m.bgStop();
		break;
	case effectOn:
		userData::sharedInstance()->setEFFECT(true);
		break;
	case effectOff:
		userData::sharedInstance()->setEFFECT(false);
		break;
	}

}
