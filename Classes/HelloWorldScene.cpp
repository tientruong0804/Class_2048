#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace std;

vector<vector<Sprite*>> vectorSprite;

Scene* HelloWorld::createScene()
{            
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    for(int i = 0; i<4; i++)
        for(int j=0; j<4; j++)
            array[i][j] = 0;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    for(int i=0; i<4; i++)
    {
        vector<Sprite*> spriteTg;

        for(int j=0; j<4; j++)
        {
            auto sprite = Sprite::create("white-square.png");
            auto x = sprite->getContentSize().width;
            auto y = (visibleSize.width / 6) / x;

            sprite->setScale(y);

            sprite->setPosition(Vec2(visibleSize.width/6 + (j*x*y), visibleSize.height*5/6 - (i * x*y)));
            sprite->setColor(Color3B::RED);
            spriteTg.push_back(sprite);
            this->addChild(sprite,0);
        }

        vectorSprite.push_back(spriteTg);
    }
/*
    auto locationSprite = vectorSprite[0][3]->getPosition();
    auto numberLable = Label::createWithTTF("2","fonts/Marker Felt.ttf", 120);
    //numberLable->setColor(Color3B::BLUED);
    numberLable->setPosition(Vec2(locationSprite.x/2,locationSprite.y/3));
    vectorSprite[0][3]->addChild(numberLable);


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

*/
    HelloWorld::showNumber();
    return true;
}

void HelloWorld::showNumber()
{
    int count = 0;
    char text[10];

    for(int i =0; i<4; i++)
        for(int j = 0; j<4; j++)
        {
            if(array[i][j] != 0)
            {
                count++;

                sprintf(text,"%d",array[i][j]);

                auto locationSprite = vectorSprite[i][j]->getPosition();
                auto numberLable = Label::createWithTTF(text,"fonts/Marker Felt.ttf", 120);
                //numberLable->setColor(Color3B::BLUED);
                numberLable->setPosition(Point(locationSprite.x/2,locationSprite.y/2));
                
                vectorSprite[i][j]->addChild(numberLable);
            }
        }

    //if(count == 16)
       // return;

    int number = cocos2d::RandomHelper::random_int(1, 2);

    while(true && count <16)
    {
        int x = cocos2d::RandomHelper::random_int(0,15);

        int h = x/4;
        int c = h%4;

        if(array[h][c] == 0)
        {
            array[h][c] = number;
            auto locationSprite = vectorSprite[h][c]->getPosition();
            sprintf(text,"%d",number);
            auto numberLable = Label::createWithTTF(text,"fonts/Marker Felt.ttf", 120);
            //numberLable->setColor(Color3B::BLUED);
            numberLable->setPosition(Point(locationSprite.x/2,locationSprite.y/2));
            //numberLable.color=ccc3(60,60,60);
            vectorSprite[h][c]->addChild(numberLable);
            break;
        }
    }
}

void HelloWorld::eventTouch()
{
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan=[&](Touch* touch, Event* event)
    {
        hStart = touch->getLocation().x;
        cStart = touch->getLocation().y;
        return true;
    };

    listener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        hEnd = touch->getLocation().x;
        cEnd = touch->getLocation().y;

        float kc = sqrt(((hEnd-hStart)*(hEnd - hStart))+((cEnd-cStart) * (cEnd - cStart)));

        if(kc > 100)
        {
            if(hEnd > hStart)
            {
                float x = hEnd-hStart;

                if(cEnd>cStart)
                {
                    float y = cEnd-cStart;
                    if(y > x)
                        HelloWorld::upMove();
                    else
                        HelloWorld::rightMove();
                }
                else
                {
                    float y = cStart-cEnd;

                    if(y >x)
                        HelloWorld::downMove();
                    else
                        HelloWorld::rightMove();
                }
            }
            else
            {
                float x = hStart-hEnd;

                if(cEnd>cStart)
                {
                    float y = cEnd-cStart;
                    if(y > x)
                        HelloWorld::upMove();
                    else
                        HelloWorld::leftMove();
                }
                else
                {
                    float y = cStart-cEnd;

                    if(y >x)
                        HelloWorld::downMove();
                    else
                        HelloWorld::leftMove();
                }

            }
        }
    };
}
/*
    void HelloWorld::eventMouse()
    {
        auto mouseListener = EventListenerMouse::create();


    }
*/

void HelloWorld::upMove()
{
    int i,j,h,c;

    for(j=0; j<4; j++)
    {
        for(i=1; i<4;i++)
        {
            if(array[i][j] != 0)
            {
                h =i;

                while(h>0)
                {
                    if(array[h-1][j] == 0)
                    {
                        array[h-1][j] = array[h][i];
                        array[h][j] = 0;
                        h--;
                    }
                    else
                    {
                        if(array[h-1][j] == array[h][j])
                        {
                            array[h-1][j] = array[h-1][j] * 2;
                            array[h][j] = 0;
                        }
                        
                        break;
                    }
                }
            }
        }
    }

    HelloWorld::showNumber();
}

void HelloWorld::downMove()
{
    int i,j,h,c;

    for(j=0; j<4; j++)
    {
        for(i=2; i>=0;i--)
        {
            if(array[i][j] != 0)
            {
                h =i;

                while(h<3)
                {
                    if(array[h+1][j] == 0)
                    {
                        array[h+1][j] = array[h][i];
                        array[h][j] = 0;
                        h++;
                    }
                    else
                    {
                        if(array[h+1][j] == array[h][j])
                        {
                            array[h+1][j] = array[h+1][j] * 2;
                            array[h][j] = 0;
                        }
                        
                        break;
                    }
                }
            }
        }
    }

    HelloWorld::showNumber();
}

void HelloWorld::leftMove()
{
    int i,j,h,c;

    for(i=0; i<4; i++)
    {
        for(j=1; j<4; j++)
        {
            c = j;

            while(j>0)
            {
                if(array[i][c-1] == 0)
                {
                    array[i][c-1] = array[i][c];
                    array[i][c] = 0;

                    c--;
                }
                else
                {
                    if(array[i][c-1] == array[i][c])
                    {
                        array[i][c-1] = array[i][c] * 2;
                        array[i][c] = 0;
                    }
                    break;
                }
            }
        }
    }

    HelloWorld::showNumber();
}

void HelloWorld::rightMove()
{
    int i,j,h,c;

    for(i=0; i<4; i++)
    {
        for(j=3; j>0; j--)
        {
            c = j;

            while(j<3)
            {
                if(array[i][c+1] == 0)
                {
                    array[i][c+1] = array[i][c];
                    array[i][c] = 0;

                    c++;
                }
                else
                {
                    if(array[i][c+1] == array[i][c])
                    {
                        array[i][c+1] = array[i][c] * 2;
                        array[i][c] = 0;
                    }
                    break;
                }
            }
        }
    }

    HelloWorld::showNumber();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
