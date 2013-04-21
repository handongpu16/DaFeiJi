#include "cocos2d.h"


//life
int g_LIFE = 4;

//score
int g_SCORE = 0;

cocos2d::CCArray* g_ENEMIES_CONTAINER = new cocos2d::CCArray(30);
cocos2d::CCArray* g_ENEMY_BULLETS_CONTAINER = new cocos2d::CCArray(1000);
cocos2d::CCArray* g_PLAYER_BULLETS_CONTAINER = new cocos2d::CCArray(1000);