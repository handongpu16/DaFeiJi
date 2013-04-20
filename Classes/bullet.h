#ifndef  _BULLET_H_
#define  _BULLET_H_

#include "cocos2d.h"
#include "AppMacros.h"

class Bullet: public cocos2d::CCSprite ,public DaFeiJiObjectInterface
{
public:
	Bullet(int,const char*,int);
	~Bullet(void);
private:
	void initialize(int bulletSpeed, const char* weaponType,int attackMode);
	void update(float dt) ;

//implement DaFeiJiObjectInterface
private:
	virtual void destroy();
	virtual bool isActive(){return active;}

public:
	void  hurt ();
public:
	   int zOrder;
private:;
   bool active;
   int xVelocity;
   int yVelocity;
   int power;
   int HP;
   int moveType;
   int attackMode;
   int parentType;
};

#endif