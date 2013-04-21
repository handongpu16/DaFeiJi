#ifndef  _SYSMENU_H_
#define  _SYSMENU_H_

#include "cocos2d.h"
class SysMenu: public cocos2d::CCLayer
{
public:
	SysMenu(void);
	~SysMenu(void);
    virtual bool init();  
	static cocos2d::CCScene* scene();

	void onNewGame(CCObject* pSender);
	void onSettings(CCObject* pSender);
	void onQuit(CCObject* pSender);
	void onAbout(CCObject* pSender);
	void onButtonEffect(CCObject* pSender);
	
	CREATE_FUNC(SysMenu);

private:
	cocos2d::CCSprite *ship;

};

#endif //_SYSMENU_H_