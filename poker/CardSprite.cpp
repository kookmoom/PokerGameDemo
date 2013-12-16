//
//  CardSprite.cpp
//  poker
//
//  Created by Artuira on 13-12-16.
//
//

#include "CardSprite.h"

//  CardSprite.cpp
//  Cocos2dev.com
//
//  Created by LiuYanghui on 13-6-17.
//
//

#include "CardSprite.h"

#define kInAngleZ        270 //里面卡牌的起始Z轴角度
#define kInDeltaZ        90  //里面卡牌旋转的Z轴角度差

#define kOutAngleZ       0   //封面卡牌的起始Z轴角度
#define kOutDeltaZ       90  //封面卡牌旋转的Z轴角度差

enum {
    tag_inCard = 1,
    tag_outCard
};

CardSprite::CardSprite()
{
    
}

CardSprite::~CardSprite()
{
    m_openAnimIn->release();
    m_openAnimOut->release();
}



CardSprite* CardSprite::create(const char* inCardImageName, const char* outCardImageName, float duration, SEL_CallFuncN selector,cocos2d::CCNode *sender)
{
    CardSprite *pSprite = new CardSprite();
    if (pSprite && pSprite->init(inCardImageName, outCardImageName, duration ,selector,sender))
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    
    return NULL;
}

bool CardSprite::init(const char* inCardImageName, const char* outCardImageName, float duration , SEL_CallFuncN selector,cocos2d::CCNode *sender)
{
    if (!CCSprite::init())
    {
        return false;
    }
    initData(inCardImageName, outCardImageName, duration,selector,sender);
    return true;
}

#pragma mark - initData
void CardSprite::initData(const char* inCardImageName, const char* outCardImageName, float duration, SEL_CallFuncN selector,cocos2d::CCNode *sender)
{
    m_isOpened = false;
    
    CCSprite* inCard = CCSprite::create(inCardImageName);
    inCard->setPosition(CCPointZero);
    inCard->setVisible(false);
    inCard->setTag(tag_inCard);
    addChild(inCard);
    
    CCSprite* outCard = CCSprite::create(outCardImageName);
    outCard->setPosition(CCPointZero);
    outCard->setTag(tag_outCard);
    addChild(outCard);
    
    m_openAnimIn = (CCActionInterval*)CCSequence::create(CCDelayTime::create(duration * .5),
                                                         CCShow::create(),
                                                         CCOrbitCamera::create(duration * .5, 1, 0, kInAngleZ, kInDeltaZ, 0, 0),
                                                         CCCallFuncN::create(sender, selector),
                                                         NULL);
    m_openAnimIn->retain();
    
    m_openAnimOut = (CCActionInterval *)CCSequence::create(CCOrbitCamera::create(duration * .5, 1, 0, kOutAngleZ, kOutDeltaZ, 0, 0),
                                                           CCHide::create(),
                                                           CCDelayTime::create(duration * .5),
                                                           CCCallFuncN::create(sender, selector),
                                                           NULL);
    m_openAnimOut->retain();
}

#pragma mark - public func
void CardSprite::openCard()
{
    CCSprite* inCard = (CCSprite*)getChildByTag(tag_inCard);
    CCSprite* outCard = (CCSprite*)getChildByTag(tag_outCard);
    inCard->runAction(m_openAnimIn);
    outCard->runAction(m_openAnimOut);
}