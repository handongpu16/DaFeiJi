#ifndef  _SYSMENU_H_
#define  _SYSMENU_H_

#include "cocos2d.h"
USING_NS_CC;

class SysMenu: public cocos2d::CCLayer
{
public:
	SysMenu(void);
	~SysMenu(void);
    virtual bool init();  
	static cocos2d::CCScene* scene();

	void onNewGame();
	void onSettings(CCObject* pSender);
	void onQuit(CCObject* pSender);
	void onAbout(CCObject* pSender);
	void onButtonEffect(CCObject* pSender);
	

	CREATE_FUNC(SysMenu);

private:
	cocos2d::CCSprite *ship;
    void onStart(CCObject* pSender);
	void flareEffect(CCLayer* parent, CCLayer* target, SEL_CallFunc callback);
    void  SysMenu::removeChild();
};

#endif //_SYSMENU_H_