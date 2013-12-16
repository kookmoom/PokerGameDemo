#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;
class HelloWorld : public cocos2d::CCLayer
{

public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // menu callback
    void menuCloseCallback(CCObject* pSender);
    void menuOfGen(CCObject* pSender);
    
    //networks callback
    void getHttpRequestCompleted(cocos2d::CCNode *sender ,void *data);
    void okHttpRequestCompleted(cocos2d::CCNode *sender ,void *data);
    
    //CardSprite callback
    void flipLeftCard(cocos2d::CCNode *sender);
    void flipRightCard(cocos2d::CCNode *sender);
    
    //touch envent callback
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    
   
    
private:
    //networks methods
    void okNetworks();
    void getNetworks();
    
    
    CCLabelAtlas * _pMyNumberLabel;
    CCLabelAtlas * _pRightPoker;
    CCLabelAtlas * _pLeftPoker;
    CCLabelTTF * _pWins;
    
    int _myNumber;
    int _compuerNumber;
    
};

#endif // __HELLOWORLD_SCENE_H__
