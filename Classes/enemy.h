#ifndef  _ENEMY_H_
#define  _ENEMY_H_

#include "cocos2d.h"
#include "AppMacros.h"

class Enemy: public cocos2d::CCSprite ,public DaFeiJiObjectInterface
{
public:
	Enemy(int enemyType);
	~Enemy(void);


static void sharedEnemy();
private:
	void initialize(int enemyType);
	void update(float dt) ;

//implement DaFeiJiObjectInterface
private:
	virtual void destroy();
	virtual bool isActive(){return active;}

public:
	void  hurt ();
	 void shoot (float dt) ;
public:
	   int zOrder;
	   int  moveType;
private:;
    int eID;
    bool active;
    int speed;
    int bulletSpeed;
    int HP;
    int bulletPowerValue;
   
    int scoreValue;
    long delayTime;
    int attackMode;
    int _hurtColorLife;
	

	char* textureName;
    char* bulletType;
};

#endif