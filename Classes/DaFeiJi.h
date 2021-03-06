#ifndef  _DAFEIJI_H_
#define  _DAFEIJI_H_

#include "cocos2d.h"

class Ship;
class LevelManager;
class DaFeiJiObjectInterface;

class DaFeiJi: public cocos2d::CCLayer
{
public:
	DaFeiJi(void);
	~DaFeiJi(void);

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(DaFeiJi);

//implement touch delegate
private:
	virtual void ccTouchesMoved(cocos2d::CCSet * touches, cocos2d::CCEvent *event);
//overwrite ccobject function
	virtual void update(float dt);
private:
	//new functions
	void initBackground();;
	void movingBackground (float dt);
	void processEvent(cocos2d::CCEvent *pEvent) ;
	void removeInactiveUnit(float dt);
	void scoreCounter(float dt);
	void checkIsCollide () ;
    bool collide(DaFeiJiObjectInterface* a,DaFeiJiObjectInterface* b) ;
	void checkIsReborn () ;
	void updateUI() ;
public:
	Ship* _ship;
private:
	cocos2d::CCSprite*    _backSky;
	cocos2d::CCSprite* _backSkyRe;
	int _backSkyHeight;
    cocos2d::CCTMXTiledMap* _backTileMap;
	cocos2d::CCTMXTiledMap* _backTileMapRe;
    int _backTileMapHeight;
	bool _isBackSkyReload;
	bool _isBackTileReload;
    cocos2d::CCSize _winSize;
	cocos2d::CCRect _screenRect;

	cocos2d::CCLabelTTF* _lbLife;
	cocos2d::CCLabelBMFont* _lbScore;
	long int _time;
	LevelManager* _levelManager;
	int _state;
	long _tmpScore;
};
#endif //_DAFEIJI_H_