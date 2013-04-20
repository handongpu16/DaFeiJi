#include "DaFeiJi.h"
#include "AppMacros.h"
#include "ship.h"
#include "SimpleAudioEngine.h"
#include "LevelManager.h"
#include "enemy.h"

USING_NS_CC;


#define MW_UNIT_TAG_PLAYER 4


DaFeiJi::DaFeiJi()
{
	_backSky = NULL;
	_backSkyHeight = 0;
	_backTileMap = NULL;
	_isBackSkyReload =false;
	_isBackTileReload = false;
	_time = 0;
	
}

DaFeiJi::~DaFeiJi(void)
{
	delete _levelManager;
}


CCScene* DaFeiJi::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    DaFeiJi *layer = DaFeiJi::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool DaFeiJi::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

		//_state = STATE_PLAYING;

		_winSize = CCDirector::sharedDirector()->getWinSize();
		initBackground();



		_levelManager = new LevelManager(this);
		Enemy::sharedEnemy();
            // ship life
		//TODO:不知道咋从CCTexture2D生成Spirit
		//CCTexture2D* shipTexture = CCTexture2D:ddImage(s_ship01);
		//CCSprite* life = CCSprite::createWithTexture(shipTexture, CCRect(0, 0, 60, 38));
		CCSprite* life = CCSprite::create(s_ship01, CCRect(0, 0, 60, 38));
        life->setScale(0.6);
		life->setPosition(CCPoint(30, 460));
        addChild(life, 1, 5);

        // ship Life count
		_lbLife = CCLabelTTF::create("0", "Arial", 20);
        _lbLife->setPosition(CCPoint(60, 463));
        _lbLife->setColor(ccRED);
        addChild(_lbLife, 1000);

        // ship
        _ship = new Ship();
        addChild(_ship, _ship->zOrder, PLAYER_TAG);
		_ship->release();

		setTouchEnabled(true);

		// schedule
        scheduleUpdate();
		schedule(schedule_selector(DaFeiJi::scoreCounter), 1);


		 if (SOUND) {
			 CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
			 CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(s_bgMusic, true);
            }
		return true;

#if 0
     // reset global values
            MW.CONTAINER.ENEMIES = [];
            MW.CONTAINER.ENEMY_BULLETS = [];
            MW.CONTAINER.PLAYER_BULLETS = [];
            MW.SCORE = 0;
            MW.LIFE = 4;
            this._state = STATE_PLAYING;

            Explosion.sharedExplosion();
            Enemy.sharedEnemy();
			winSize = CCDirector::getWinSize();
            this._levelManager = new LevelManager(this);
            this.initBackground();
            this.screenRect = cc.rect(0, 0, winSize.width, winSize.height + 10);

            // score
            this.lbScore = cc.LabelBMFont.create("Score: 0", s_arial14_fnt);
            this.lbScore.setAnchorPoint( cc.p(1,0) );
            this.lbScore.setAlignment( cc.TEXT_ALIGNMENT_RIGHT );
            this.addChild(this.lbScore, 1000);
            this.lbScore.setPosition(cc.p(winSize.width - 5 , winSize.height - 30));

            // ship life
            var shipTexture = cc.TextureCache.getInstance().addImage(s_ship01);
            var life = cc.Sprite.createWithTexture(shipTexture, cc.rect(0, 0, 60, 38));
            life.setScale(0.6);
            life.setPosition(cc.p(30, 460));
            this.addChild(life, 1, 5);

            // ship Life count
            this._lbLife = cc.LabelTTF.create("0", "Arial", 20);
            this._lbLife.setPosition(cc.p(60, 463));
            this._lbLife.setColor(cc.RED);
            this.addChild(this._lbLife, 1000);

            // ship
            this._ship = new Ship();
            this.addChild(this._ship, this._ship.zOrder, MW.UNIT_TAG.PLAYER);

            // accept touch now!

            var t = cc.config.deviceType;
            if( t == 'browser' )  {
                this.setTouchEnabled(true);
                this.setKeyboardEnabled(true);
            } else if( t == 'desktop' ) {
                this.setMouseEnabled(true);
            } else if( t == 'mobile' ) {
                this.setTouchEnabled(true);
            }

            // schedule
            this.scheduleUpdate();
            this.schedule(this.scoreCounter, 1);

            if (MW.SOUND) {
                cc.AudioEngine.getInstance().playBackgroundMusic(s_bgMusic, true);
            }

            bRet = true;

#endif

}


void DaFeiJi::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}





   void DaFeiJi::initBackground() {
        // bg
	    _backSky = CCSprite::create(s_bg01);
		_backSky->setAnchorPoint(CCPoint(0, 0));
		_backSkyHeight = _backSky->getContentSize().height;
        addChild(_backSky, -10);

        //tilemap
		_backTileMap = CCTMXTiledMap::create(s_level01);
        addChild(_backTileMap, -9);
        _backTileMapHeight = _backTileMap->getMapSize().height * _backTileMap->getTileSize().height;

        _backSkyHeight -= 48;
        _backTileMapHeight -= 200;
		_backSky->runAction(CCMoveBy::create(3, CCPoint(0, -48)));
		_backTileMap->runAction(CCMoveBy::create(3, CCPoint(0, -200)));

        schedule(schedule_selector(DaFeiJi::movingBackground), 3);
    }

   void DaFeiJi::movingBackground (float dt)
   {
        _backSky->runAction(CCMoveBy::create(3, CCPoint(0, -48)));
        _backTileMap->runAction(CCMoveBy::create(3, CCPoint(0, -200)));
        _backSkyHeight -= 48;
        _backTileMapHeight -= 200;

        if (_backSkyHeight <= _winSize.height) {
            if (!_isBackSkyReload) {
				_backSkyRe = CCSprite::create(s_bg01);
				_backSkyRe->setAnchorPoint(CCPoint(0, 0));
                addChild(_backSkyRe, -10);
                _backSkyRe->setPosition(CCPoint(0, _winSize.height));
                _isBackSkyReload = true;
            }
            _backSkyRe->runAction(CCMoveBy::create(3, CCPoint(0, -48)));
        }
        if (_backSkyHeight <= 0) {
            _backSkyHeight = _backSky->getContentSize().height;
            removeChild(_backSky, true);
            _backSky = _backSkyRe;
            _backSkyRe = NULL;
            _isBackSkyReload = false;
        }

        if (_backTileMapHeight <= _winSize.height) {
            if (!_isBackTileReload) {
				_backTileMapRe = CCTMXTiledMap::create(s_level01);
                addChild(_backTileMapRe, -9);
                _backTileMapRe->setPosition(CCPoint(0, _winSize.height));
                _isBackTileReload = true;
            }
            _backTileMapRe->runAction(CCMoveBy::create(3, CCPoint(0, -200)));
        }

        if (_backTileMapHeight <= 0) {
            _backTileMapHeight = _backTileMapRe->getMapSize().height * _backTileMapRe->getTileSize().height;
            removeChild(_backTileMap, true);
            _backTileMap = _backTileMapRe;
            _backTileMapRe = NULL;
            _isBackTileReload = false;
        }
    }

void DaFeiJi::ccTouchesMoved(CCSet * touches, CCEvent *event)
{
	CCSetIterator it = touches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	CCPoint start = touch->getLocation();    
	CCPoint delta = touch->getDelta();
	CCPoint curPos = _ship->getPosition();
	curPos= ccpAdd( curPos, delta );
	curPos = ccpClamp(curPos, CCPoint(), CCPoint(_winSize.width, _winSize.height) );
	_ship->setPosition( curPos );
}


//void DaFeiJi::onMouseDragged( event ) {
//    this.processEvent( event );
//}

void DaFeiJi::processEvent(CCEvent *pEvent) {
    //if( _state == STATE_PLAYING ) {
  //      CCPoint delta = pEvent->getDelta();
  //      CCPoint curPos = _ship->getPosition();
  //      curPos= ccpAdd( curPos, delta );
		//curPos = ccpClamp(curPos, CCPoint(), CCPoint(_winSize.width, _winSize.height) );
  //      _ship->setPosition( curPos );
   // }
}

void DaFeiJi::update(float dt) {
       // if( _state == STATE_PLAYING ) {
            //checkIsCollide();
            removeInactiveUnit(dt);
           // checkIsReborn();
           // updateUI();
     //   }

        //if( cc.config.deviceType == 'browser' )
        //    cc.$("#cou").innerHTML = "Ship:" + 1 + ", Enemy: " + MW.CONTAINER.ENEMIES.length + ", Bullet:" + MW.CONTAINER.ENEMY_BULLETS.length + "," + MW.CONTAINER.PLAYER_BULLETS.length + " all:" + this.getChildren().length;
}

void DaFeiJi::removeInactiveUnit(float dt) {
        CCNode* selChild = NULL;
		CCArray*  layerChildren = getChildren();
		for (unsigned int i =0 ;i< layerChildren->count();i++) {
            selChild = (CCNode*)layerChildren->objectAtIndex(i);
            if (selChild) {
 //              if( typeof selChild.update == 'function' ) {
					selChild->update(dt);
                    int tag = selChild->getTag();
					printf("tag  = %d \n",tag);
                    if ((tag == PLAYER_TAG) || (tag == PLAYER_BULLET_TAG) ||
                        (tag == ENEMY_TAG) || (tag == ENMEY_BULLET_TAG)) {
						DaFeiJiObjectInterface* selChildInterface = dynamic_cast<DaFeiJiObjectInterface*>(selChild);
                        if (!selChildInterface->isActive()) {
                            selChildInterface->destroy();
                        }
//                  }
                }
            }
        }
    }



void DaFeiJi::scoreCounter(float dt) 
{
        //if( this._state == STATE_PLAYING ) {
            _time++;

			//没用吧
            //int minute = 0 | (_time / 60);
            //int second = _time % 60;
            //minute = minute > 9 ? minute : "0" + minute;
            //second = second > 9 ? second : "0" + second;
            //var curTime = minute + ":" + second;
            _levelManager->loadLevelResource(_time);
       // }
}


#if 0
STATE_PLAYING = 0;
STATE_GAMEOVER = 1;

var GameLayer = cc.Layer.extend({
    _time:null,
    _ship:null,
    _backSky:null,
    _backSkyHeight:0,
    _backSkyRe:null,
    _backTileMap:null,
    _backTileMapHeight:0,
    _backTileMapRe:null,
    _levelManager:null,
    _tmpScore:0,
    _isBackSkyReload:false,
    _isBackTileReload:false,
    lbScore:null,
    screenRect:null,
    explosionAnimation:[],
    _beginPos:cc.p(0, 0),
    _state:STATE_PLAYING,
    ctor:function () {
        cc.associateWithNative( this, cc.Layer );
    },
    init:function () {
        var bRet = false;
        if (this._super()) {

            // reset global values
            MW.CONTAINER.ENEMIES = [];
            MW.CONTAINER.ENEMY_BULLETS = [];
            MW.CONTAINER.PLAYER_BULLETS = [];
            MW.SCORE = 0;
            MW.LIFE = 4;
            this._state = STATE_PLAYING;

            Explosion.sharedExplosion();
            Enemy.sharedEnemy();
            winSize = cc.Director.getInstance().getWinSize();
            this._levelManager = new LevelManager(this);
            this.initBackground();
            this.screenRect = cc.rect(0, 0, winSize.width, winSize.height + 10);

            // score
            this.lbScore = cc.LabelBMFont.create("Score: 0", s_arial14_fnt);
            this.lbScore.setAnchorPoint( cc.p(1,0) );
            this.lbScore.setAlignment( cc.TEXT_ALIGNMENT_RIGHT );
            this.addChild(this.lbScore, 1000);
            this.lbScore.setPosition(cc.p(winSize.width - 5 , winSize.height - 30));

            // ship life
            var shipTexture = cc.TextureCache.getInstance().addImage(s_ship01);
            var life = cc.Sprite.createWithTexture(shipTexture, cc.rect(0, 0, 60, 38));
            life.setScale(0.6);
            life.setPosition(cc.p(30, 460));
            this.addChild(life, 1, 5);

            // ship Life count
            this._lbLife = cc.LabelTTF.create("0", "Arial", 20);
            this._lbLife.setPosition(cc.p(60, 463));
            this._lbLife.setColor(cc.RED);
            this.addChild(this._lbLife, 1000);

            // ship
            this._ship = new Ship();
            this.addChild(this._ship, this._ship.zOrder, MW.UNIT_TAG.PLAYER);

            // accept touch now!

            var t = cc.config.deviceType;
            if( t == 'browser' )  {
                this.setTouchEnabled(true);
                this.setKeyboardEnabled(true);
            } else if( t == 'desktop' ) {
                this.setMouseEnabled(true);
            } else if( t == 'mobile' ) {
                this.setTouchEnabled(true);
            }

            // schedule
            this.scheduleUpdate();
            this.schedule(this.scoreCounter, 1);

            if (MW.SOUND) {
                cc.AudioEngine.getInstance().playBackgroundMusic(s_bgMusic, true);
            }

            bRet = true;
        }
        return bRet;
    },
    scoreCounter:function () {
        if( this._state == STATE_PLAYING ) {
            this._time++;

            var minute = 0 | (this._time / 60);
            var second = this._time % 60;
            minute = minute > 9 ? minute : "0" + minute;
            second = second > 9 ? second : "0" + second;
            var curTime = minute + ":" + second;
            this._levelManager.loadLevelResource(this._time);
        }
    },

    onTouchesMoved:function (touches, event) {
        this.processEvent( touches[0] );
    },

    onMouseDragged:function( event ) {
        this.processEvent( event );
    },

    processEvent:function( event ) {
        if( this._state == STATE_PLAYING ) {
            var delta = event.getDelta();
            var curPos = this._ship.getPosition();
            curPos= cc.pAdd( curPos, delta );
            curPos = cc.pClamp(curPos, cc.POINT_ZERO, cc.p(winSize.width, winSize.height) );
            this._ship.setPosition( curPos );
        }
    },

    onKeyDown:function (e) {
        MW.KEYS[e] = true;
    },

    onKeyUp:function (e) {
        MW.KEYS[e] = false;
    },

    update:function (dt) {
        if( this._state == STATE_PLAYING ) {
            this.checkIsCollide();
            this.removeInactiveUnit(dt);
            this.checkIsReborn();
            this.updateUI();
        }

        if( cc.config.deviceType == 'browser' )
            cc.$("#cou").innerHTML = "Ship:" + 1 + ", Enemy: " + MW.CONTAINER.ENEMIES.length + ", Bullet:" + MW.CONTAINER.ENEMY_BULLETS.length + "," + MW.CONTAINER.PLAYER_BULLETS.length + " all:" + this.getChildren().length;
    },
    checkIsCollide:function () {
        var selChild, bulletChild;
        //check collide
        var i =0;
        for (i = 0; i < MW.CONTAINER.ENEMIES.length; i++) {
            selChild = MW.CONTAINER.ENEMIES[i];
            for (var j = 0; j < MW.CONTAINER.PLAYER_BULLETS.length; j++) {
                bulletChild = MW.CONTAINER.PLAYER_BULLETS[j];
                if (this.collide(selChild, bulletChild)) {
                    bulletChild.hurt();
                    selChild.hurt();
                }
                if (!cc.rectIntersectsRect(this.screenRect, bulletChild.getBoundingBox() )) {
                    bulletChild.destroy();
                }
            }
            if (this.collide(selChild, this._ship)) {
                if (this._ship.active) {
                    selChild.hurt();
                    this._ship.hurt();
                }
            }
            if (!cc.rectIntersectsRect(this.screenRect, selChild.getBoundingBox() )) {
                selChild.destroy();
            }
        }

        for (i = 0; i < MW.CONTAINER.ENEMY_BULLETS.length; i++) {
            selChild = MW.CONTAINER.ENEMY_BULLETS[i];
            if (this.collide(selChild, this._ship)) {
                if (this._ship.active) {
                    selChild.hurt();
                    this._ship.hurt();
                }
            }
            if (!cc.rectIntersectsRect(this.screenRect, selChild.getBoundingBox() )) {
                selChild.destroy();
            }
        }
    },
    removeInactiveUnit:function (dt) {
        var selChild, layerChildren = this.getChildren();
        for (var i in layerChildren) {
            selChild = layerChildren[i];
            if (selChild) {
                if( typeof selChild.update == 'function' ) {
                    selChild.update(dt);
                    var tag = selChild.getTag();
                    if ((tag == MW.UNIT_TAG.PLAYER) || (tag == MW.UNIT_TAG.PLAYER_BULLET) ||
                        (tag == MW.UNIT_TAG.ENEMY) || (tag == MW.UNIT_TAG.ENMEY_BULLET)) {
                        if (selChild && !selChild.active) {
                            selChild.destroy();
                        }
                    }
                }
            }
        }
    },
    checkIsReborn:function () {
        if (MW.LIFE > 0 && !this._ship.active) {
            // ship
            this._ship = new Ship();
            this.addChild(this._ship, this._ship.zOrder, MW.UNIT_TAG.PLAYER);
        }
        else if (MW.LIFE <= 0 && !this._ship.active) {
            this._state = STATE_GAMEOVER;
            // XXX: needed for JS bindings.
            this._ship = null;
            this.runAction(cc.Sequence.create(
                cc.DelayTime.create(0.2),
                cc.CallFunc.create(this, this.onGameOver)));
        }
    },
    updateUI:function () {
        if (this._tmpScore < MW.SCORE) {
            this._tmpScore += 5;
        }
        this._lbLife.setString(MW.LIFE);
        this.lbScore.setString("Score: " + this._tmpScore);
    },
    collide:function (a, b) {
        var aRect = a.collideRect();
        var bRect = b.collideRect();
        if (cc.rectIntersectsRect(aRect, bRect)) {
            return true;
        }
    },
    initBackground:function () {
        // bg
        this._backSky = cc.Sprite.create(s_bg01);
        this._backSky.setAnchorPoint(cc.p(0, 0));
        this._backSkyHeight = this._backSky.getContentSize().height;
        this.addChild(this._backSky, -10);

        //tilemap
        this._backTileMap = cc.TMXTiledMap.create(s_level01);
        this.addChild(this._backTileMap, -9);
        this._backTileMapHeight = this._backTileMap.getMapSize().height * this._backTileMap.getTileSize().height;

        this._backSkyHeight -= 48;
        this._backTileMapHeight -= 200;
        this._backSky.runAction(cc.MoveBy.create(3, cc.p(0, -48)));
        this._backTileMap.runAction(cc.MoveBy.create(3, cc.p(0, -200)));

        this.schedule(this.movingBackground, 3);
    },
    movingBackground:function () {
        this._backSky.runAction(cc.MoveBy.create(3, cc.p(0, -48)));
        this._backTileMap.runAction(cc.MoveBy.create(3, cc.p(0, -200)));
        this._backSkyHeight -= 48;
        this._backTileMapHeight -= 200;

        if (this._backSkyHeight <= winSize.height) {
            if (!this._isBackSkyReload) {
                this._backSkyRe = cc.Sprite.create(s_bg01);
                this._backSkyRe.setAnchorPoint(cc.p(0, 0));
                this.addChild(this._backSkyRe, -10);
                this._backSkyRe.setPosition(cc.p(0, winSize.height));
                this._isBackSkyReload = true;
            }
            this._backSkyRe.runAction(cc.MoveBy.create(3, cc.p(0, -48)));
        }
        if (this._backSkyHeight <= 0) {
            this._backSkyHeight = this._backSky.getContentSize().height;
            this.removeChild(this._backSky, true);
            this._backSky = this._backSkyRe;
            this._backSkyRe = null;
            this._isBackSkyReload = false;
        }

        if (this._backTileMapHeight <= winSize.height) {
            if (!this._isBackTileReload) {
                this._backTileMapRe = cc.TMXTiledMap.create(s_level01);
                this.addChild(this._backTileMapRe, -9);
                this._backTileMapRe.setPosition(cc.p(0, winSize.height));
                this._isBackTileReload = true;
            }
            this._backTileMapRe.runAction(cc.MoveBy.create(3, cc.p(0, -200)));
        }
        if (this._backTileMapHeight <= 0) {
            this._backTileMapHeight = this._backTileMapRe.getMapSize().height * this._backTileMapRe.getTileSize().height;
            this.removeChild(this._backTileMap, true);
            this._backTileMap = this._backTileMapRe;
            this._backTileMapRe = null;
            this._isBackTileReload = false;
        }
    },
    onGameOver:function () {
        var scene = cc.Scene.create();
        scene.addChild(GameOver.create());
        cc.Director.getInstance().replaceScene(cc.TransitionFade.create(1.2, scene));
    }
});

GameLayer.create = function () {
    var sg = new GameLayer();
    if (sg && sg.init()) {
        return sg;
    }
    return null;
};

GameLayer.scene = function () {
    var scene = cc.Scene.create();
    var layer = GameLayer.create();
    scene.addChild(layer, 1);
    return scene;
};
#endif