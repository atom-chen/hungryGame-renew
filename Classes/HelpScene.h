#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace ui;

class HelpScene : public LayerColor
{
public:
	
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::Scene* createScene();

	void menu_closeHelpScene(Object*); // µµ¿ò¸»Ã¢À» ´ÝÀ½

	CREATE_FUNC(HelpScene);

	std::string helpType;

public:
	virtual void onEnter();
	virtual void onExit();

	ScrollView* scrollView;
};

#endif //__HELP_SCENE_H__
