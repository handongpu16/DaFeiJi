#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

/* For demonstrating using one design resolution to match different resources,
   or one resource to match different design resolutions.

   [Situation 1] Using one design resolution to match different resources.
     Please look into Appdelegate::applicationDidFinishLaunching.
     We check current device frame size to decide which resource need to be selected.
     So if you want to test this situation which said in title '[Situation 1]',
     you should change ios simulator to different device(e.g. iphone, iphone-retina3.5, iphone-retina4.0, ipad, ipad-retina),
     or change the window size in "proj.XXX/main.cpp" by "CCEGLView::setFrameSize" if you are using win32 or linux plaform
     and modify "proj.mac/AppController.mm" by changing the window rectangle.

   [Situation 2] Using one resource to match different design resolutions.
     The coordinates in your codes is based on your current design resolution rather than resource size.
     Therefore, your design resolution could be very large and your resource size could be small.
     To test this, just define the marco 'TARGET_DESIGN_RESOLUTION_SIZE' to 'DESIGN_RESOLUTION_2048X1536'
     and open iphone simulator or create a window of 480x320 size.

   [Note] Normally, developer just need to define one design resolution(e.g. 960x640) with one or more resources.
 */

#define DESIGN_RESOLUTION_480X320    0
#define DESIGN_RESOLUTION_1024X768   1
#define DESIGN_RESOLUTION_2048X1536  2

/* If you want to switch design resolution, change next line */
#define TARGET_DESIGN_RESOLUTION_SIZE  DESIGN_RESOLUTION_2048X1536

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];
}Resource;

static Resource smallResource  =  { cocos2d::CCSizeMake(480, 320),   "iphone" };
static Resource mediumResource =  { cocos2d::CCSizeMake(1024, 768),  "ipad"   };
static Resource largeResource  =  { cocos2d::CCSizeMake(2048, 1536), "ipadhd" };

//new resource
static Resource winResource  =  { cocos2d::CCSizeMake(320, 480),  "win"   };
static const char s_bg01[]                = "bg01.jpg";
static const char s_level01[]             = "level01.tmx";
static const char s_ship01[]              = "ship01.png";
static const char s_bullet_plist[]        = "bullet.plist";
static const char s_bgMusic[]			  = "Music/bgMusic.mp3"; //TODO:
static const char s_Enemy_plist[]		  = "Enemy.plist";
static const char s_Enemy[]				  = "Enemy.png";
static const char s_shipDestroyEffect[]			  = "Music/shipDestroyEffect.mp3"; 
static const char s_explodeEffect[]			  = "Music/explodeEffect.mp3"; 
static const char s_explosion_plist[]			  = "explosion.plist"; 
static const char s_arial14_fnt[]			  = "arial-14.fnt"; 
static const char s_menu[]			  = "menu.png";
static const char s_loading[]			  = "loading.png";
static const char s_logo[]			  = "logo.png";




#if (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_480X320)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(480, 320);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_1024X768)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);
#elif (TARGET_DESIGN_RESOLUTION_SIZE == DESIGN_RESOLUTION_2048X1536)
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(2048, 1536);
#else
#error unknown target design resolution!
#endif

// The font size 24 is designed for small resolution, so we should change it to fit for current design resolution
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / smallResource.size.width * 24)



//game state
enum GAME_STATE {
    HOME =0,
    PLAY =1,
    OVER =2
};

//keys
//MW.KEYS = [];

//level
enum LEVEL {
    STAGE1 =1,
    STAGE2 =2,
    STAGE3 =3
};

//life
extern int g_LIFE;

//score
extern int g_SCORE;

//sound
static const bool SOUND = true;

//enemy move type
enum ENEMY_MOVE_TYPE {
    ATTACK =0,
    VERTICAL =1,
    HORIZONTAL =2,
    OVERLAP =3
};

//delta x
static const int DELTA_X = -100;

//offset x
static const int OFFSET_X = -24;

//rot
static const float ROT = -5.625;

//bullet type
enum BULLET_TYPE {
    PLAYER =1,
    ENEMY =2
};

//weapon type
enum WEAPON_TYPE {
    ONE =1
};

//unit tag
enum UNIT_TAG{
    ENMEY_BULLET_TAG =900,
    PLAYER_BULLET_TAG =901,
    ENEMY_TAG =1000,
    PLAYER_TAG =1001
};

//attack mode
enum ENEMY_ATTACK_MODE {
    NORMAL =1,
    TSUIHIKIDAN =2
};

//life up sorce
static const int LIFEUP_SORCE[] = {50000, 100000, 150000, 200000, 250000, 300000};



extern cocos2d::CCArray* g_ENEMIES_CONTAINER ;
extern cocos2d::CCArray* g_ENEMY_BULLETS_CONTAINER ;
extern cocos2d::CCArray* g_PLAYER_BULLETS_CONTAINER ;


class DaFeiJiObjectInterface{
public:
	virtual void destroy() = 0;
	virtual bool isActive() = 0;
	virtual cocos2d::CCRect collideRect() = 0;
	virtual void hurt() = 0;
};















































#endif /* __APPMACROS_H__ */
