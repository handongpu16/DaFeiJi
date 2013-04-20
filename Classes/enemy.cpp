#include "enemy.h"
#include "math.h"
#include "bullet.h"
USING_NS_CC;

Enemy::Enemy(int enemyType)
{
    eID =0;
    active = true;
    speed = 200;
    bulletSpeed = -200;
    HP = 15;
    bulletPowerValue = 1;
    moveType = 0;
    scoreValue = 200;
    zOrder = 1000;
	delayTime = 1 + 1.2 * CCRANDOM_0_1();
    attackMode = NORMAL;
    _hurtColorLife = 0;

	initialize(enemyType);
}



Enemy::~Enemy(void)
{
}


void Enemy::initialize(int enemyType)
{

	switch(enemyType)
	{
	case 0:
		{
        textureName = "E0.png";
        bulletType = "W2.png";
        HP =1;
		moveType = ENEMY_MOVE_TYPE::OVERLAP;
		attackMode = ENEMY_ATTACK_MODE::NORMAL;
        scoreValue = 15;
		}
		break;
	case 1:
		{
        textureName = "E1.png";
        bulletType = "W2.png";
        HP = 2;
		moveType = ENEMY_MOVE_TYPE::ATTACK;
		attackMode = ENEMY_ATTACK_MODE::NORMAL;
        scoreValue = 40;
		}
		break;
	case 2:
		{
        textureName = "E2.png";
        bulletType = "W2.png";
        HP = 4;
		moveType = ENEMY_MOVE_TYPE::HORIZONTAL;
		attackMode = ENEMY_ATTACK_MODE::TSUIHIKIDAN;
        scoreValue = 60;
		}
		break;
	case 3:
		{
        textureName = "E3.png";
        bulletType = "W2.png";
        HP = 6;
		moveType = ENEMY_MOVE_TYPE::OVERLAP;
		attackMode = ENEMY_ATTACK_MODE::NORMAL;
        scoreValue = 80;
		}
		break;
	default:
		break;
	}

	//TODO: 根据类型创建敌人
    //{
    //    type:0,
    //    textureName:"E0.png",
    //    bulletType:"W2.png",
    //    HP:1,
    //    moveType:MW.ENEMY_MOVE_TYPE.ATTACK,
    //    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    //    scoreValue:15
    //},
    //{
    //    type:1,
    //    textureName:"E1.png",
    //    bulletType:"W2.png",
    //    HP:2,
    //    moveType:MW.ENEMY_MOVE_TYPE.ATTACK,
    //    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    //    scoreValue:40
    //},
    //{
    //    type:2,
    //    textureName:"E2.png",
    //    bulletType:"W2.png",
    //    HP:4,
    //    moveType:MW.ENEMY_MOVE_TYPE.HORIZONTAL,
    //    attackMode:MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN,
    //    scoreValue:60
    //},
    //{
    //    type:3,
    //    textureName:"E3.png",
    //    bulletType:"W2.png",
    //    HP:6,
    //    moveType:MW.ENEMY_MOVE_TYPE.OVERLAP,
    //    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    //    scoreValue:80
    //},
    //{
    //    type:4,
    //    textureName:"E4.png",
    //    bulletType:"W2.png",
    //    HP:10,
    //    moveType:MW.ENEMY_MOVE_TYPE.HORIZONTAL,
    //    attackMode:MW.ENEMY_ATTACK_MODE.TSUIHIKIDAN,
    //    scoreValue:150
    //},
    //{
    //    type:5,
    //    textureName:"E5.png",
    //    bulletType:"W2.png",
    //    HP:15,
    //    moveType:MW.ENEMY_MOVE_TYPE.HORIZONTAL,
    //    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    //    scoreValue:200
    //}

    initWithSpriteFrameName(textureName);
	schedule(schedule_selector(Enemy::shoot), delayTime);
}


 void  Enemy::update(float dt) 
{
       if (HP <= 0) {
            active = false;
        }
	   //TODO:
//        _timeTick += dt;
//        if (_timeTick > 0.1) {
//            _timeTick = 0;
//            if (_hurtColorLife > 0) {
//                _hurtColorLife--;
//            }
//            if (_hurtColorLife == 1) {
//                setColor( cc.WHITE );
//            }
//        }
}

 

 void Enemy::destroy () {
        g_SCORE += scoreValue;
        //var a = new Explosion();
        //a.setPosition(this.getPosition());
        //this.getParent().addChild(a);
        //spark(this.getPosition(),this.getParent(), 1.2, 0.7);
		g_ENEMIES_CONTAINER->removeObject(this);
        removeFromParentAndCleanup(true);
        //if(MW.SOUND){
        //    cc.AudioEngine.getInstance().playEffect(s_explodeEffect);
        //}
    }

 void  Enemy::hurt () {
        HP--;
    }


 void Enemy::shoot (float dt) 
 {
         CCPoint p = getPosition();
        Bullet* b = new Bullet(bulletSpeed, "W2.png", attackMode);
        g_ENEMY_BULLETS_CONTAINER->addObject(b);
		b->release();
        getParent()->addChild(b, b->zOrder, ENMEY_BULLET_TAG);
        b->setPosition(CCPoint(p.x, p.y - getContentSize().height * 0.2));
 }

 void Enemy::sharedEnemy()
 {
	 CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_Enemy_plist, s_Enemy);
}


#if 0
var Enemy = cc.Sprite.extend({
    eID:0,
    active:true,
    speed:200,
    bulletSpeed:-200,
    HP:15,
    bulletPowerValue:1,
    moveType:null,
    scoreValue:200,
    zOrder:1000,
    delayTime:1 + 1.2 * Math.random(),
    attackMode:MW.ENEMY_MOVE_TYPE.NORMAL,
    _hurtColorLife:0,
    ctor:function (arg) {
        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Sprite );

        this.HP = arg.HP;
        this.moveType = arg.moveType;
        this.scoreValue = arg.scoreValue;
        this.attackMode = arg.attackMode;

        this.initWithSpriteFrameName(arg.textureName);
        this.schedule(this.shoot, this.delayTime);
    },
    _timeTick:0,
    update:function (dt) {
        if (this.HP <= 0) {
            this.active = false;
        }
        this._timeTick += dt;
        if (this._timeTick > 0.1) {
            this._timeTick = 0;
            if (this._hurtColorLife > 0) {
                this._hurtColorLife--;
            }
            if (this._hurtColorLife == 1) {
                this.setColor( cc.WHITE );
            }
        }
    },
    destroy:function () {
        MW.SCORE += this.scoreValue;
        var a = new Explosion();
        a.setPosition(this.getPosition());
        this.getParent().addChild(a);
        spark(this.getPosition(),this.getParent(), 1.2, 0.7);
        cc.ArrayRemoveObject(MW.CONTAINER.ENEMIES,this);
        this.removeFromParentAndCleanup(true);
        if(MW.SOUND){
            cc.AudioEngine.getInstance().playEffect(s_explodeEffect);
        }
    },
    shoot:function () {
        var p = this.getPosition();
        var b = new Bullet(this.bulletSpeed, "W2.png", this.attackMode);
        MW.CONTAINER.ENEMY_BULLETS.push(b);
        this.getParent().addChild(b, b.zOrder, MW.UNIT_TAG.ENMEY_BULLET);
        b.setPosition(cc.p(p.x, p.y - this.getContentSize().height * 0.2));
    },
    hurt:function () {
        this._hurtColorLife = 2;
        this.HP--;
        this.setColor( cc.RED );
    },
    collideRect:function(){
        var a = this.getContentSize();
        var p = this.getPosition();
        return cc.rect(p.x - a.width/2, p.y - a.height/4,a.width,a.height/2);
    }
});

Enemy.sharedEnemy = function(){
    cc.SpriteFrameCache.getInstance().addSpriteFrames(s_Enemy_plist, s_Enemy);
};


#endif