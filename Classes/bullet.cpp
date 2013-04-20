#include "bullet.h"

USING_NS_CC;

Bullet::Bullet(int bulletSpeed, const char* weaponType,int attackMode)
{
	 active =true;
    xVelocity =0;
    yVelocity = 200;
    power = 1;
    HP = 1;
    moveType = NULL;
    zOrder = 3000 ;
    attackMode = NORMAL ;
    parentType = PLAYER ;

	initialize(bulletSpeed,weaponType,attackMode);
}



Bullet::~Bullet(void)
{
}


void Bullet::initialize(int bulletSpeed, const char* weaponType,int attackMode)
{
        yVelocity = -bulletSpeed;
        attackMode = attackMode;
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_bullet_plist);
        initWithSpriteFrameName(weaponType);

		ccBlendFunc bf = {GL_SRC_ALPHA, GL_ONE};
        setBlendFunc(bf);
        /*var tmpAction;
         switch (this.attackMode) {
         case MW.ENEMY_MOVE_TYPE.NORMAL:
         tmpAction = cc.MoveBy.create(2, cc.p(this.getPosition().x, 400));
         break;
         case MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN:
         tmpAction = cc.MoveTo.create(2, GameLayer.create()._ship.getPosition());
         break;
         }
         this.runAction(tmpAction);*/
}


 void  Bullet::update(float dt) 
{
        CCPoint p = getPosition();
        p.x -= xVelocity * dt;
        p.y -= yVelocity * dt;
        setPosition( p );



        if (HP <= 0 || isMovedOutOfScreen()) {
            active = false;
        }
}

 bool  Bullet::isMovedOutOfScreen() {
 
	 CCPoint p = getPosition();
	 CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	 return p.x< 0 || p.y < 0 || p.x > screenSize.width || p.y > screenSize.height;
 }
 

 void Bullet::destroy () {
	 //TODO:±¬Õ¨Ð§¹û
        //var explode = cc.Sprite.create(s_hit);
        //explode.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
        //explode.setPosition(this.getPosition());
        //explode.setRotation(Math.random()*360);
        //explode.setScale(0.75);
        //this.getParent().addChild(explode,9999);
		g_ENEMY_BULLETS_CONTAINER->removeObject(this);
        g_ENEMY_BULLETS_CONTAINER->removeObject(this);
        removeFromParentAndCleanup(true);
	
	//var removeExplode = cc.CallFunc.create(explode, function(sender) {
	//	explode.removeFromParentAndCleanup(true);
	//    });

 //       explode.runAction(cc.ScaleBy.create(0.3, 2,2));
 //       explode.runAction(cc.Sequence.create(cc.FadeOut.create(0.3), removeExplode));
    }

 void  Bullet::hurt () {
        HP--;
    }

#if 0
var Bullet = cc.Sprite.extend({
    active:true,
    xVelocity:0,
    yVelocity:200,
    power:1,
    HP:1,
    moveType:null,
    zOrder:3000,
    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    parentType:MW.BULLET_TYPE.PLAYER,
    ctor:function (bulletSpeed, weaponType, attackMode) {
        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Sprite );

        this.yVelocity = -bulletSpeed;
        this.attackMode = attackMode;
        cc.SpriteFrameCache.getInstance().addSpriteFrames(s_bullet_plist);
        this.initWithSpriteFrameName(weaponType);
        this.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
        /*var tmpAction;
         switch (this.attackMode) {
         case MW.ENEMY_MOVE_TYPE.NORMAL:
         tmpAction = cc.MoveBy.create(2, cc.p(this.getPosition().x, 400));
         break;
         case MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN:
         tmpAction = cc.MoveTo.create(2, GameLayer.create()._ship.getPosition());
         break;
         }
         this.runAction(tmpAction);*/
    },
    update:function (dt) {
        var p = this.getPosition();
        p.x -= this.xVelocity * dt;
        p.y -= this.yVelocity * dt;
        this.setPosition( p );
        if (this.HP <= 0) {
            this.active = false;
        }
    },
    destroy:function () {
        var explode = cc.Sprite.create(s_hit);
        explode.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
        explode.setPosition(this.getPosition());
        explode.setRotation(Math.random()*360);
        explode.setScale(0.75);
        this.getParent().addChild(explode,9999);
        cc.ArrayRemoveObject(MW.CONTAINER.ENEMY_BULLETS,this);
        cc.ArrayRemoveObject(MW.CONTAINER.PLAYER_BULLETS,this);
        this.removeFromParentAndCleanup(true);
	
	var removeExplode = cc.CallFunc.create(explode, function(sender) {
		explode.removeFromParentAndCleanup(true);
	    });

        explode.runAction(cc.ScaleBy.create(0.3, 2,2));
        explode.runAction(cc.Sequence.create(cc.FadeOut.create(0.3), removeExplode));
    },
    hurt:function () {
        this.HP--;
    },
    collideRect:function(){
        var p = this.getPosition();
        return cc.rect(p.x - 3, p.y - 3, 6, 6);
    }
});

#endif