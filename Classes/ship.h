#ifndef  _SHIP_H_
#define  _SHIP_H_

#include "cocos2d.h"
#include "AppMacros.h"

class Ship: public cocos2d::CCSprite, public DaFeiJiObjectInterface
{
public:
	Ship(void);
	~Ship(void);

	cocos2d::CCRect collideRect();
private:
	void initialize();
	void shoot(float dt);

//implement DaFeiJiObjectInterface
public:
	void destroy();
	bool isActive(){return active;}
//overwrite CCObject function
private:
	void update (float dt);



public:
	void  hurt();
	int zOrder;
private:;
   int speed;
   int bulletSpeed;
   int HP;
   int bulletTypeValue;
   int bulletPowerValue;
   bool throwBombing;
   bool canBeAttack;
   bool isThrowingBomb;

   int maxBulletPowerValue;
   cocos2d::CCPoint appearPosition;
   int _hurtColorLife;
   bool active;
   float _timeTick;
};

#endif //_SHIP_H_