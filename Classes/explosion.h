#ifndef  _EXPLOSION_H_
#define  _EXPLOSION_H_

#include "cocos2d.h"
#include "AppMacros.h"

class Explosion: public cocos2d::CCSprite
{
public:
	Explosion(void);
	~Explosion(void);
private:
	void destroy ();
	static std::string iToString(int id);
public:
	static void sharedExplosion() ;

private:
    int tmpWidth;
    int tmpHeight;
};

#endif //_SHIP_H_