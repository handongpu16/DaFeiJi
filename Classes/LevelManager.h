#ifndef  _LEVELMANAGER_H_
#define  _LEVELMANAGER_H_

#include "cocos2d.h"
#include "AppMacros.h"
class  DaFeiJi;

class LevelManager
{
public:
	LevelManager(DaFeiJi* daFeiji);
	~LevelManager();

	void loadLevelResource(long deltaTime);
private:
	void addEnemyToGameLayer(int enemyType);
private:
	DaFeiJi* _gameLayer;

};

#endif