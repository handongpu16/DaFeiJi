#include "ship.h"
#include "bullet.h"

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
    //init life
	initWithFile(s_ship01, CCRect(0, 0, 60, 38));

    setTag(zOrder);
    setPosition(appearPosition);

	//TODO:加上动画
    //// set frame
    //var frame0 = cc.SpriteFrame.createWithTexture(shipTexture, cc.rect(0, 0, 60, 38));
    //var frame1 = cc.SpriteFrame.createWithTexture(shipTexture, cc.rect(60, 0, 60, 38));

    //var animFrames = [];
    //animFrames.push(frame0);
    //animFrames.push(frame1);

    //// ship animate
    //var animation = cc.Animation.create(animFrames, 0.1);
    //var animate = cc.Animate.create(animation);
    //this.runAction(cc.RepeatForever.create(animate));

	schedule(schedule_selector(Ship::shoot), (float)1/6);

	//TODO:
    ////revive effect
    //this.canBeAttack = false;
    //var ghostSprite = cc.Sprite.createWithTexture(shipTexture, cc.rect(0, 45, 60, 38));
    //ghostSprite.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
    //ghostSprite.setScale(8);
    //ghostSprite.setPosition(cc.p(this.getContentSize().width / 2, 12));
    //this.addChild(ghostSprite, 3000, 99999);
    //ghostSprite.runAction(cc.ScaleTo.create(0.5, 1, 1));
    //var blinks = cc.Blink.create(3, 9);
    //var makeBeAttack = cc.CallFunc.create(this, function (t) {
    //    t.canBeAttack = true;
    //    t.setVisible(true);
    //    t.removeChild(ghostSprite,true);
    //});
    //this.runAction(cc.Sequence.create(cc.DelayTime.create(0.5), blinks, makeBeAttack));
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
		//TODO:飞机添加爆炸效果
        //myParent->addChild( new Explosion(p) );
        myParent->removeChild(this,true);
		//TODO:添加爆炸声音
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