#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace std;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

   // vector<vector<Sprite*>> vectorSprite;
    float hStart, hEnd,cStart,cEnd;

    int array[5][5];

    virtual bool init();

    void showNumber();
    void eventTouch();
    void eventMouse();
    
    void upMove();
    void downMove();
    void leftMove();
    void rightMove();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
