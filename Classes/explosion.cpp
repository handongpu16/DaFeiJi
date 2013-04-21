#include "explosion.h"

USING_NS_CC;
using namespace std;

Explosion::Explosion(void)
{
    tmpWidth = 0;
    tmpHeight = 0;

	CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
    initWithSpriteFrame(pFrame);

    CCSize cs = getContentSize();
    tmpWidth = cs.width;
    tmpHeight = cs.height;

	CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName("Explosion");
	CCFiniteTimeAction* sequence = CCSequence::create(CCAnimate::create(animation),CCCallFunc::create(this, callfunc_selector(Explosion::destroy)) ,NULL);
	runAction(sequence);
	ccBlendFunc func ={GL_SRC_ALPHA, GL_ONE};
    setBlendFunc(func);
}

Explosion::~Explosion(void)
{

}


void Explosion::destroy () {
        getParent()->removeChild(this,true);
    }

void Explosion::sharedExplosion() 
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(s_explosion_plist);
	CCArray* animFrames = CCArray::createWithCapacity(35);

	string prefix("");
	char str[100] = {0};
    for (int i = 1; i < 35; i++) {
        sprintf(str, "explosion_%02d.png", i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
    }
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animFrames, 0.04);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Explosion");
};


#if 0
var Explosion = cc.Sprite.extend({
    tmpWidth:0,
    tmpHeight:0,
    ctor:function () {
        // needed for JS-Bindings compatibility
        cc.associateWithNative( this, cc.Sprite );

        var pFrame = cc.SpriteFrameCache.getInstance().getSpriteFrame("explosion_01.png");
        this.initWithSpriteFrame(pFrame);

        var cs = this.getContentSize();
        this.tmpWidth = cs.width;
        this.tmpHeight = cs.height;

        var animation = cc.AnimationCache.getInstance().getAnimation("Explosion");
        this.runAction(cc.Sequence.create(
            cc.Animate.create(animation),
            cc.CallFunc.create(this, this.destroy)
        ));
        this.setBlendFunc(gl.SRC_ALPHA, gl.ONE);
    },
    destroy:function () {
        this.getParent().removeChild(this,true);
    }
});

Explosion.sharedExplosion = function () {
    cc.SpriteFrameCache.getInstance().addSpriteFrames(s_explosion_plist);
    var animFrames = [];
    var str = "";
    for (var i = 1; i < 35; i++) {
        str = "explosion_" + (i < 10 ? ("0" + i) : i) + ".png";
        var frame = cc.SpriteFrameCache.getInstance().getSpriteFrame(str);
        animFrames.push(frame);
    }
    var animation = cc.Animation.create(animFrames, 0.04);
    cc.AnimationCache.getInstance().addAnimation(animation, "Explosion");
};
#endif