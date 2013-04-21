#include "ship.h"
#include "bullet.h"
#include "explosion.h"

#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

Ship::Ship():
appearPosition(160,60)
{
   speed = 220;
   bulletSpeed = 900;
   HP = 5;
   bulletTypeValue = 1;
   bulletPowerValue = 1;
   throwBombing = false;
   canBeAttack = true;
   isThrowingBomb = false;
   zOrder = 3000;
   maxBulletPowerValue = 4;
   _hurtColorLife = 0;
   active = true;

   initialize();
}
Ship::~Ship(void)
{

}


void Ship::initialize()
{
	CCTexture2D* shipTexture = CCTextureCache::sharedTextureCache()->addImage(s_ship01);
    initWithTexture(shipTexture, CCRect(0, 0, 60, 38));

    //setTag(PLAYER_TAG);
    setPosition(appearPosition);

    // set frame
	CCSpriteFrame* frame0 = CCSpriteFrame::createWithTexture(shipTexture, CCRect(0, 0, 60, 38));
	CCSpriteFrame* frame1 = CCSpriteFrame::createWithTexture(shipTexture, CCRect(60, 0, 60, 38));

	CCArray* animFrames = CCArray::createWithCapacity(4);
    animFrames->addObject(frame0);
	animFrames->addObject(frame1);

    // ship animate
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.1);
	CCAnimate* animate = CCAnimate::create(animation);
	runAction(CCRepeatForever::create(animate));

	schedule(schedule_selector(Ship::shoot), (float)1/6);


    //revive effect
    canBeAttack = false;
	ghostSprite = CCSprite::createWithTexture(shipTexture, CCRect(0, 45, 60, 38));
	ccBlendFunc fun = {GL_SRC_ALPHA, GL_ONE};
    ghostSprite->setBlendFunc(fun);
    ghostSprite->setScale(8);
    ghostSprite->setPosition(CCPoint(getContentSize().width / 2, 12));
    addChild(ghostSprite, 3000, 99999);
	ghostSprite->runAction(CCScaleTo::create(0.5, 1, 1));

	CCBlink* blinks = CCBlink::create(3, 9);
	CCCallFunc* makeBeAttack = CCCallFunc::create(this,callfunc_selector(Ship::callBack) );
	runAction(CCSequence::create(CCDelayTime::create(0.5), blinks, makeBeAttack,NULL));
}

void Ship::callBack() {
        canBeAttack = true;
        setVisible(true);
        removeChild(ghostSprite,true);
    }

void Ship::update (float dt) {

        //// Keys are only enabled on the browser
        //if( cc.config.deviceType == 'browser' ) {
        //    var pos = this.getPosition();
        //    if ((MW.KEYS[cc.KEY.w] || MW.KEYS[cc.KEY.up]) && pos.y <= winSize.height) {
        //        pos.y += dt * this.speed;
        //    }
        //    if ((MW.KEYS[cc.KEY.s] || MW.KEYS[cc.KEY.down]) && pos.y >= 0) {
        //        pos.y -= dt * this.speed;
        //    }
        //    if ((MW.KEYS[cc.KEY.a] || MW.KEYS[cc.KEY.left]) && pos.x >= 0) {
        //        pos.x -= dt * this.speed;
        //    }
        //    if ((MW.KEYS[cc.KEY.d] || MW.KEYS[cc.KEY.right]) && pos.x <= winSize.width) {
        //        pos.x += dt * this.speed;
        //    }
        //    this.setPosition( pos );
        //}

        if (HP <= 0) {
            active = false;
        }

        //_timeTick += dt;
        //if (_timeTick > 0.1) {
        //    _timeTick = 0;
        //    if (_hurtColorLife > 0) {
        //        _hurtColorLife--;
        //    }
        //    if (_hurtColorLife == 1) {
        //        setColor(ccWHITE);
        //    }
        //}
    }


void Ship::shoot (float dt) {
	//TODO:加上子弹效果
        //this.shootEffect();
        int offset = 13;
        CCPoint p = getPosition();
        CCSize cs = getContentSize();
        Bullet* a = new Bullet(bulletSpeed, "W1.png",NORMAL);

		g_PLAYER_BULLETS_CONTAINER->addObject(a);

        getParent()->addChild(a, a->zOrder, PLAYER_BULLET_TAG);

		a->release();
        a->setPosition(CCPoint(p.x + offset, p.y + 3 + cs.height * 0.3));

        Bullet* b = new Bullet(bulletSpeed, "W1.png",NORMAL);
        g_PLAYER_BULLETS_CONTAINER->addObject(b);
        getParent()->addChild(b, b->zOrder, PLAYER_BULLET_TAG);

		b->release();
        b->setPosition(CCPoint(p.x - offset, p.y + 3 + cs.height * 0.3));
    }



void Ship::destroy()
{
        g_LIFE--;
        CCPoint p = getPosition();
        CCNode* myParent = getParent();
		Explosion* exp = new Explosion();
		exp->setPosition(p);
		myParent->addChild(exp);
		exp->release();
        myParent->removeChild(this,true);
        if (SOUND) {
			SimpleAudioEngine::sharedEngine()->playEffect(s_shipDestroyEffect);
        }
}

void Ship::hurt() 
{
    if (canBeAttack) {
        _hurtColorLife = 2;
        HP--;
        setColor(ccRED);
    }
}

CCRect Ship::collideRect()
{
    CCPoint p = getPosition();
    CCSize a = getContentSize();
    return CCRect(p.x - a.width/2, p.y - a.height/2, a.width, a.height/2);
     
}