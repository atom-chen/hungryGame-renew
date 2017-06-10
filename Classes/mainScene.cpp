#include "mainScene.h"
#include "music.h"
#include "HelpScene.h"
#include "BuildingScene.h"
#include "MakerInfoScene.h"
#include "optionScene.h"

Scene* mainScene::createScene()
{
    Scene *scene = Scene::create();
    // 'layer' is an autorelease object
    mainScene *layer = mainScene::create();
    // add layer as a child to scene
    scene->addChild(layer);
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool mainScene::init()
{
    if(! LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    Size size = Director::getInstance()->getVisibleSize();
    
    if(!SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/background.mp3", true);
    
    // background image
    Sprite *pMainBg = Sprite::create("img/main_bg.png");
    pMainBg->setPosition(Vec2(size.width/2, size.height/2));
    pMainBg->setScale(size.width/pMainBg->getContentSize().width);
    this->addChild(pMainBg, 1);
    
    auto startBtn = Button::create("img/main_btn_gamestart.png", "img/main_btn_gamestart_c.png");
    startBtn->setPosition(Vec2(size.width /2 , 1000 ));
    startBtn->setTag(1);
    startBtn->addTouchEventListener(CC_CALLBACK_2(mainScene::menuBtnsCallback, this));
    this->addChild(startBtn, 2);
    
    auto optionBtn = Button::create("img/main_btn_option.png","img/main_btn_option_c.png");
    optionBtn->setPosition(Vec2(size.width /2 , 800 ));
    optionBtn->setTag(2);
    optionBtn->addTouchEventListener(CC_CALLBACK_2(mainScene::menuBtnsCallback, this));
    this->addChild(optionBtn, 2);
    
    auto helpBtn = Button::create("img/main_btn_help.png", "img/main_btn_help_n.png");
    helpBtn->setPosition(Vec2(size.width / 2 , 600 ));
    helpBtn->setTag(3);
    helpBtn->addTouchEventListener(CC_CALLBACK_2(mainScene::menuBtnsCallback, this));
    this->addChild(helpBtn, 2);
    
    auto creditBtn = Button::create("img/main_btn_info.png",
                                    "img/main_btn_info_n.png");
    creditBtn->setPosition(Vec2(size.width /2 , 400 ));
    creditBtn->setTag(4);
    creditBtn->addTouchEventListener(CC_CALLBACK_2(mainScene::menuBtnsCallback, this));
    this->addChild(creditBtn, 2);
    
    auto endBtn = Button::create("img/main_btn_endgame.png","img/main_btn_endgame_n.png");
    endBtn->setPosition(Vec2(size.width / 2 , 200));
    endBtn->setTag(5);
    endBtn->addTouchEventListener(CC_CALLBACK_2(mainScene::menuBtnsCallback, this));
    this->addChild(endBtn, 2);
    
    //scale
    float scaleF = 1.5f;
    startBtn->setScale(scaleF);
    optionBtn->setScale(scaleF);
    helpBtn->setScale(scaleF);
    creditBtn->setScale(scaleF);
    endBtn->setScale(scaleF);
    
    return true;
}


void mainScene::menuBtnsCallback(cocos2d::Ref *pSender, ui::Button::TouchEventType type)
{
    auto btn = (Button*)pSender;
    int tag = btn->getTag();
    if(Button::TouchEventType::ENDED == type)
    {
        SimpleAudioEngine::getInstance()->playEffect("sound/effect_btn_click.mp3");
        switch (tag) {
            case 1:
            {//start
                Scene *pScene = BuildingScene::createScene();
                auto trans = TransitionFade::create(0.5f, pScene);
                Director::getInstance()->replaceScene(trans);
            }
                break;
            case 2:
            {//option
                Scene *pScene = OptionScene::createScene();
                auto trans = TransitionFade::create(0.5f, pScene);
                Director::getInstance()->replaceScene(trans);
            }
                break;
            case 3:
            {//help
                Scene *pScene = HelpScene::createScene();
                auto trans = TransitionFade::create(0.5f, pScene);
                Director::getInstance()->replaceScene(trans);
            }
                break;
            case 4:
            {//credit
                Scene *pScene = MakerInfoScene::createScene();
                auto trans = TransitionFade::create(0.5f, pScene);
                Director::getInstance()->replaceScene(trans);
            }
                break;
            case 5:
            {//exit
                Director::getInstance()->end();
            }
                break;
            default:
                break;
        }
    }
    
}
