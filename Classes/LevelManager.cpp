#include "LevelManager.h"
#include "DaFeiJi.h"
#include "enemy.h"
#include "ship.h"


USING_NS_CC;


LevelManager::LevelManager(DaFeiJi* daFeiji)
{
	_gameLayer = daFeiji;
}

LevelManager::~LevelManager()
{

}


void LevelManager::loadLevelResource(long deltaTime)
{
        //load enemy
        //for(var i = 0; i< this._currentLevel.enemies.length; i++){
        //    var selEnemy = this._currentLevel.enemies[i];
        //    if(selEnemy){
        //        if(selEnemy.ShowType == "Once"){
        //            if(selEnemy.ShowTime == deltaTime){
        //                for(var tIndex = 0; tIndex < selEnemy.Types.length;tIndex++ ){
        //					addEnemyToGameLayer(selEnemy.Types[tIndex]);
        //                }
        //            }
        //        }else if(selEnemy.ShowType == "Repeate"){
        //            if(deltaTime % selEnemy.ShowTime === 0){
        //                for(var rIndex = 0; rIndex < selEnemy.Types.length;rIndex++ ){
        //                    this.addEnemyToGameLayer(selEnemy.Types[rIndex]);
        //                }
        //            }
        //        }
        //    }
        //}
		if( deltaTime % 5 ==0){
			addEnemyToGameLayer(0);
		}else if(deltaTime % 7 ==0)
			addEnemyToGameLayer(1);
		else if(deltaTime % 8==0)
			addEnemyToGameLayer(2);
}


void LevelManager::addEnemyToGameLayer(int enemyType)
{
        Enemy* addEnemy = new Enemy(enemyType);

		CCSize winSize =  CCDirector::sharedDirector()->getWinSize();
		CCPoint enemypos = CCPoint( 80 + (winSize.width - 160) * (int)CCRANDOM_0_1(), winSize.height);
        CCSize enemycs =  addEnemy->getContentSize();
        addEnemy->setPosition( enemypos );
        

        CCPoint offset;
		CCAction* tmpAction = NULL;
        CCMoveBy * a0= NULL;
        CCMoveBy * a1= NULL;
        switch (addEnemy->moveType) {
			case ENEMY_MOVE_TYPE::ATTACK:
                offset = _gameLayer->_ship->getPosition();
				tmpAction = CCMoveTo::create(1, offset);
                break;
				//TODO:加上不同类行运动的敌人
			case ENEMY_MOVE_TYPE::VERTICAL:
                offset = CCPoint(0, -winSize.height - enemycs.height);
				tmpAction = CCMoveBy::create(4, offset);
                break;
			//case ENEMY_MOVE_TYPE::HORIZONTAL:
   //             offset = CCPoint(0, -100 - 200 * (int)CCRANDOM_0_1());
			//	a0 = CCMoveBy::create(0.5, offset);
			//	a1 = CCMoveBy::create(1, CCPoint(-50 - 100 * Math.random(), 0));
			//	CCCallFunc::create(addEnemy, ) ;
			//	var onComplete = {
   //                 var a2 = cc.DelayTime.create(1);
   //                 var a3 = cc.MoveBy.create(1, cc.p(100 + 100 * Math.random(), 0));
   //                 pSender.runAction(cc.RepeatForever.create(
   //                     cc.Sequence.create(a2, a3, a2.copy(), a3.reverse())
   //                 ));
   //             });
			//	tmpAction = CCSequence::create(a0, a1, onComplete);
   //             break;
			case ENEMY_MOVE_TYPE::OVERLAP:
                int newX = (enemypos.x <= winSize.width / 2) ? 320 : -320;
				a0 = CCMoveBy::create(4, CCPoint(newX, -240));
				a1 = CCMoveBy::create(4, CCPoint(-newX,-320));
				tmpAction = CCSequence::create(a0,a1,NULL);
                break;
        }
		if(tmpAction){
		    _gameLayer->addChild(addEnemy, addEnemy->zOrder,ENEMY_TAG);
			g_ENEMIES_CONTAINER->addObject(addEnemy);
			addEnemy->runAction(tmpAction);
		}
		addEnemy->release();
    }

#if 0
   loadLevelResource:function(deltaTime){
        //load enemy
        for(var i = 0; i< this._currentLevel.enemies.length; i++){
            var selEnemy = this._currentLevel.enemies[i];
            if(selEnemy){
                if(selEnemy.ShowType == "Once"){
                    if(selEnemy.ShowTime == deltaTime){
                        for(var tIndex = 0; tIndex < selEnemy.Types.length;tIndex++ ){
                            this.addEnemyToGameLayer(selEnemy.Types[tIndex]);
                        }
                    }
                }else if(selEnemy.ShowType == "Repeate"){
                    if(deltaTime % selEnemy.ShowTime === 0){
                        for(var rIndex = 0; rIndex < selEnemy.Types.length;rIndex++ ){
                            this.addEnemyToGameLayer(selEnemy.Types[rIndex]);
                        }
                    }
                }
            }
        }
    },

    addEnemyToGameLayer:function(enemyType){
        var addEnemy = new Enemy(EnemyType[enemyType]);

        var enemypos = cc.p( 80 + (winSize.width - 160) * Math.random(), winSize.height);
        var enemycs =  addEnemy.getContentSize();
        addEnemy.setPosition( enemypos );
        

        var offset, tmpAction;
        var a0=0;
        var a1=0;
        switch (addEnemy.moveType) {
            case MW.ENEMY_MOVE_TYPE.ATTACK:
                offset = this._gameLayer._ship.getPosition();
                tmpAction = cc.MoveTo.create(1, offset);
                break;
            case MW.ENEMY_MOVE_TYPE.VERTICAL:
                offset = cc.p(0, -winSize.height - enemycs.height);
                tmpAction = cc.MoveBy.create(4, offset);
                break;
            case MW.ENEMY_MOVE_TYPE.HORIZONTAL:
                offset = cc.p(0, -100 - 200 * Math.random());
                a0 = cc.MoveBy.create(0.5, offset);
                a1 = cc.MoveBy.create(1, cc.p(-50 - 100 * Math.random(), 0));
                var onComplete = cc.CallFunc.create(addEnemy, function (pSender) {
                    var a2 = cc.DelayTime.create(1);
                    var a3 = cc.MoveBy.create(1, cc.p(100 + 100 * Math.random(), 0));
                    pSender.runAction(cc.RepeatForever.create(
                        cc.Sequence.create(a2, a3, a2.copy(), a3.reverse())
                    ));
                });
                tmpAction = cc.Sequence.create(a0, a1, onComplete);
                break;
            case MW.ENEMY_MOVE_TYPE.OVERLAP:
                var newX = (enemypos.x <= winSize.width / 2) ? 320 : -320;
                a0 = cc.MoveBy.create(4, cc.p(newX, -240));
                a1 = cc.MoveBy.create(4,cc.p(-newX,-320));
                tmpAction = cc.Sequence.create(a0,a1);
                break;
        }

        this._gameLayer.addChild(addEnemy, addEnemy.zOrder, MW.UNIT_TAG.ENEMY);
        MW.CONTAINER.ENEMIES.push(addEnemy);
        addEnemy.runAction(tmpAction);
    }

#endif