//
//  CardSprite.h
//  poker
//
//  Created by Artuira on 13-12-16.
//
//

#ifndef poker_CardSprite_h
#define poker_CardSprite_h


#include "cocos2d.h"
USING_NS_CC;

class CardSprite : public CCSprite
{
public:
    CardSprite();
    ~CardSprite();
//    static CardSprite* create(const char* inCardImageName, const char* outCardImageName, float duration);
    virtual bool init(const char* inCardImageName, const char* outCardImageName, float duration, SEL_CallFuncN selector ,cocos2d::CCNode *sender);
    
    static CardSprite* create(const char* inCardImageName, const char* outCardImageName, float duration, SEL_CallFuncN selector, cocos2d::CCNode *sender);
    
private:
    bool m_isOpened;
    CCActionInterval* m_openAnimIn;
    CCActionInterval* m_openAnimOut;
    SEL_CallFunc m_callBack;
    
    void initData(const char* inCardImageName, const char* outCardImageName, float duration, SEL_CallFuncN selector,cocos2d::CCNode *sender);
    
public:
    void openCard();
};


#endif
