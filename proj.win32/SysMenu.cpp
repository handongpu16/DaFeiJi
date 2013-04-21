#include "SysMenu.h"
#include "AppMacros.h"
#include "DaFeiJi.h"
USING_NS_CC;

SysMenu::SysMenu(void):ship(NULL)
{
}

SysMenu::~SysMenu(void)
{
}

CCScene* SysMenu::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        SysMenu *layer = SysMenu::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool SysMenu::init()
{
    bool bRet = false;
	do
	{
		CC_BREAK_IF(! CCLayer::init());
		/*
		winSize = cc.Director.getInstance().getWinSize();
            var sp = cc.Sprite.create(s_loading);
            sp.setAnchorPoint(cc.p(0,0));
            this.addChild(sp, 0, 1);

            var logo = cc.Sprite.create(s_logo);
            logo.setAnchorPoint(cc.p(0, 0));
            logo.setPosition(cc.p(0, 250));
            this.addChild(logo, 10, 1);

            var newGameNormal = cc.Sprite.create(s_menu, cc.rect(0, 0, 126, 33));
            var newGameSelected = cc.Sprite.create(s_menu, cc.rect(0, 33, 126, 33));
            var newGameDisabled = cc.Sprite.create(s_menu, cc.rect(0, 33 * 2, 126, 33));

            var gameSettingsNormal = cc.Sprite.create(s_menu, cc.rect(126, 0, 126, 33));
            var gameSettingsSelected = cc.Sprite.create(s_menu, cc.rect(126, 33, 126, 33));
            var gameSettingsDisabled = cc.Sprite.create(s_menu, cc.rect(126, 33 * 2, 126, 33));

            var aboutNormal = cc.Sprite.create(s_menu, cc.rect(252, 0, 126, 33));
            var aboutSelected = cc.Sprite.create(s_menu, cc.rect(252, 33, 126, 33));
            var aboutDisabled = cc.Sprite.create(s_menu, cc.rect(252, 33 * 2, 126, 33));

            var newGame = cc.MenuItemSprite.create(newGameNormal, newGameSelected, newGameDisabled, this, function () {
                this.onButtonEffect();
                flareEffect(this, this, this.onNewGame);
            });
            var gameSettings = cc.MenuItemSprite.create(gameSettingsNormal, gameSettingsSelected, gameSettingsDisabled, this, this.onSettings);
            var about = cc.MenuItemSprite.create(aboutNormal, aboutSelected, aboutDisabled, this, this.onAbout);

            var menu = cc.Menu.create(newGame, gameSettings, about);
            menu.alignItemsVerticallyWithPadding(10);
            this.addChild(menu, 1, 2);
            menu.setPosition(cc.p(winSize.width / 2, winSize.height / 2 - 80));
            this.schedule(this.update, 0.1);

            var tmp = cc.TextureCache.getInstance().addImage(s_ship01);
            this._ship = cc.Sprite.createWithTexture(tmp,cc.rect(0, 45, 60, 38));
            this.addChild(this._ship, 0, 4);
            var pos = cc.p(Math.random() * winSize.width, 0);
            this._ship.setPosition( pos );
            this._ship.runAction(cc.MoveBy.create(2, cc.p(Math.random() * winSize.width, pos.y + winSize.height + 100)));

            if (MW.SOUND) {
                cc.AudioEngine.getInstance().setBackgroundMusicVolume(0.7);
                cc.AudioEngine.getInstance().playBackgroundMusic(s_mainMainMusic, true);
            }
		*/
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCSprite *loading = CCSprite::create(s_loading);
		CC_BREAK_IF(! loading);
		loading->setAnchorPoint(ccp(0,0));
        this->addChild(loading, 0, 1);
		
		CCSprite *logo = CCSprite::create(s_logo);
		CC_BREAK_IF(! logo);
        logo->setAnchorPoint(ccp(0, 0));
        logo->setPosition(ccp(0, 250));
        this->addChild(logo, 10, 1);

		CCSprite *newGameNormal = CCSprite::create(s_menu, CCRect(0, 0, 126, 33));
        CCSprite *newGameSelected = CCSprite::create(s_menu, CCRect(0, 33, 126, 33));
        CCSprite *newGameDisabled = CCSprite::create(s_menu, CCRect(0, 33 * 2, 126, 33));

        CCSprite *gameSettingsNormal = CCSprite::create(s_menu, CCRect(126, 0, 126, 33));
        CCSprite *gameSettingsSelected = CCSprite::create(s_menu, CCRect(126, 33, 126, 33));
        CCSprite *gameSettingsDisabled = CCSprite::create(s_menu, CCRect(126, 33 * 2, 126, 33));

        CCSprite *aboutNormal = CCSprite::create(s_menu, CCRect(252, 0, 126, 33));
        CCSprite *aboutSelected = CCSprite::create(s_menu, CCRect(252, 33, 126, 33));
        CCSprite *aboutDisabled = CCSprite::create(s_menu, CCRect(252, 33 * 2, 126, 33));

		CCMenuItemSprite *newGame = CCMenuItemSprite::create(newGameNormal, 
			newGameSelected, 
			newGameDisabled,
			this, 
			//function () {
            //    this.onButtonEffect();
            //   flareEffect(this, this, this.onNewGame);
			//}
			menu_selector(SysMenu::onNewGame)
		);
		CCMenuItemSprite *gameSettings = CCMenuItemSprite::create(gameSettingsNormal, 
			gameSettingsSelected, 
			gameSettingsDisabled, 
			this, 
			menu_selector(SysMenu::onSettings));

		CCMenuItemSprite *about = CCMenuItemSprite::create(aboutNormal, aboutSelected, 
			aboutDisabled, 
			this, 
			menu_selector(SysMenu::onAbout));

		CCMenu *menu = CCMenu::create(newGame, gameSettings, about,NULL);
        menu->alignItemsVerticallyWithPadding(10);
        this->addChild(menu, 1, 2);
        menu->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 80));
		this->schedule(schedule_selector(SysMenu::update), 0.1);

		CCTexture2D *tmp = CCTextureCache::sharedTextureCache()->addImage(s_ship01);
		this->ship = CCSprite::createWithTexture(tmp,CCRect(0, 45, 60, 38));
        this->addChild(this->ship, 0, 4);
        CCPoint pos = ccp(CCRANDOM_0_1() * winSize.width, 0);
        this->ship->setPosition( pos );
		this->ship->runAction(CCMoveBy::create(2, ccp(CCRANDOM_0_1() * winSize.width, pos.y + winSize.height + 100)));

		bRet = true;
	}while(0);
	return bRet;
}



void SysMenu ::onNewGame(CCObject* pSender)
{
	CCScene *scene = CCScene::create();
	scene->addChild(DaFeiJi::create());
    //scene.addChild(GameControlMenu.create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.2, scene));
}

void SysMenu::onSettings(CCObject* pSender)
{
}

void SysMenu::onQuit(CCObject* pSender)
{
}

void SysMenu::onAbout(CCObject* pSender)
{
}

void SysMenu::onButtonEffect(CCObject* pSender)
{
}

