#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
#include "CardSprite.h"
#include   <unistd.h>

USING_NS_CC_EXT;
using namespace cocos2d;
using namespace CocosDenshion;

//tag
#define GETTAG 1
#define OKTAG 2
#define LEFTPOKERTAG 3
#define RIGHTPOKERTAG 4
#define SCORETAG 5

// position and distance
#define LABEL_DISTANCE_ONE_NUMBER ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 460)
#define LABEL_DISTANCE_TWO_NUMBER ccp(CCDirector::sharedDirector()->getWinSize().width - 330, 460)
#define LABEL_DISTANCE_THREE_NUMBER ccp(CCDirector::sharedDirector()->getWinSize().width - 360, 460)

#define LABEL_POSITION_LEFTPOKER ccp(CCDirector::sharedDirector()->getWinSize().width - 850, 280)
#define LABEL_POSITION_RIGHTPOKER ccp(CCDirector::sharedDirector()->getWinSize().width - 155, 280)
#define LABEL_POSITION_WINS ccp(CCDirector::sharedDirector()->getWinSize().width - 450, 300)
#define LABEL_POSITION_MYNUMBER  ccp(CCDirector::sharedDirector()->getWinSize().width - 330, 460)

#define MENU_POSITION_CLOSE ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20)
#define MENU_POSITION_GEN ccp(CCDirector::sharedDirector()->getWinSize().width - 450, 150)

#define SPRITE_POSITION_LEFTPOKER ccp(CCDirector::sharedDirector()->getWinSize().width - 800,300)
#define SPRITE_POSITION_RIGHTPOKER ccp(CCDirector::sharedDirector()->getWinSize().width - 100,300)
#define SPRITE_POSITION_OK ccp(CCDirector::sharedDirector()->getWinSize().width - 300, 150)
#define SPRITE_POSITION_GET ccp(CCDirector::sharedDirector()->getWinSize().width - 600, 150)
#define SPRITE_POSITION_SCORE ccp(CCDirector::sharedDirector()->getWinSize().width - 450, 500)


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    this->setTouchEnabled(true);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                          "CloseNormal.png",
                                                          "CloseSelected.png",
                                                          this,
                                                          menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition(MENU_POSITION_CLOSE );
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    
    // create gen menu
    CCMenuItemImage *ptestItem1 = CCMenuItemImage::create("gen.png", "gen.png",this,menu_selector(HelloWorld::menuOfGen));
    
    ptestItem1->setPosition(MENU_POSITION_GEN);
    CCMenu *ptestMenu1 = CCMenu::create(ptestItem1,NULL);
    ptestMenu1->setPosition(CCPointZero);
    this->addChild(ptestMenu1,5);
    
    
    /////////////////////////////
    // 3. add your codes below...
    
 
    // create label of pokers
    
    _pRightPoker = CCLabelAtlas::create("0123456789", "bignumber.png", 36, 80, '0') ;
    _pLeftPoker = CCLabelAtlas::create("0123456789", "bignumber.png", 36, 80, '0') ;
    
    _pRightPoker->setPosition(LABEL_POSITION_RIGHTPOKER);
    _pLeftPoker->setPosition( LABEL_POSITION_LEFTPOKER);
    
    _pLeftPoker->setString("");
    _pRightPoker->setString("");
    
    this->addChild(_pRightPoker,10);
    this->addChild(_pLeftPoker,11);
    
    //create label of Wins
    _pWins = CCLabelTTF::create("0","Marker Felt",50);
    _pWins->setPosition(LABEL_POSITION_WINS);
    this->addChild(_pWins);
    
    //create label of mynumber
    _pMyNumberLabel = CCLabelAtlas::create("0123456789", "scorenumber.png", 34, 60, '0') ;
    
    _pMyNumberLabel->setPosition( LABEL_POSITION_MYNUMBER);
    
    
    _pMyNumberLabel->setString("98");

    this->addChild(_pMyNumberLabel, 1);
    
    // add my number sprite
    CCSprite *pScore = CCSprite::create("scoreframe.png");
    pScore->setPosition(SPRITE_POSITION_SCORE);
    pScore->setTag(SCORETAG);
    
    this->addChild(pScore);
    
    // add two poker sprites
    CardSprite *pPokerLeftSide = CardSprite::create("poker.png","poker.png",1,callfuncN_selector(HelloWorld::flipLeftCard),this);
    CardSprite *pPokerRightSide = CardSprite::create("poker.png","poker.png",1,callfuncN_selector(HelloWorld::flipRightCard),this);
    
    pPokerLeftSide->setPosition(SPRITE_POSITION_LEFTPOKER);
    pPokerRightSide->setPosition(SPRITE_POSITION_RIGHTPOKER);
    pPokerLeftSide->setTag(LEFTPOKERTAG);
    pPokerRightSide->setTag(RIGHTPOKERTAG);
    
    this->addChild(pPokerRightSide, 1);
    this->addChild(pPokerLeftSide, 2);
    
    
    // add get and ok item for action 
    CCSprite *getItem = CCSprite::create("get.png");
    getItem->setPosition(SPRITE_POSITION_GET);
    getItem->setTag(GETTAG);
    
    CCSprite *okItem = CCSprite::create("ok.png");
    okItem->setPosition(SPRITE_POSITION_OK);
    okItem->setTag(OKTAG);
    
    this->addChild(getItem);
    this->addChild(okItem);
    
    return true;
}

// menucallback

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuOfGen(CCObject* pSender)
{
    //clear the number in the poker
    _pLeftPoker->setString("");
    _pRightPoker->setString("");
    
    //create random number
    _myNumber = arc4random()%101;
    _compuerNumber = arc4random()%101;
    
    char *temp = new char[64];
    sprintf(temp, "%d",_myNumber);
    
    //dislay the number for right position
    if (_myNumber <= 9) {
        
        _pMyNumberLabel->setPosition( LABEL_DISTANCE_ONE_NUMBER );
        _pMyNumberLabel->setString(temp);
    }
    else if (_myNumber <= 99)
    {
        _pMyNumberLabel->setPosition( LABEL_DISTANCE_TWO_NUMBER );
        _pMyNumberLabel->setString(temp);
    }
    else
    {
        _pMyNumberLabel->setPosition( LABEL_DISTANCE_THREE_NUMBER );
        _pMyNumberLabel->setString(temp);
    }
    
    
}

// networks methods

void HelloWorld::okNetworks()
{
    //uodate the score to the server
    
    //flip the poker card
    CardSprite *pcardRight = (CardSprite*)this->getChildByTag(RIGHTPOKERTAG);
    CardSprite *pcardLeft = (CardSprite*)this->getChildByTag(LEFTPOKERTAG);
    pcardRight->openCard();
    pcardLeft->openCard();
    
    //find the winer and update score
    char *temp = new char[64];
    
    if (_myNumber > _compuerNumber) {
        
        sprintf(temp, "%d",_myNumber);
        
        std::string myscore = temp;
        
        cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
        
        
        std::string str1 = "http://localhost/gen.php?";
        std::string str2 = str1+"password="+temp;
        request->setUrl(str2.c_str());
        request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
        request->setResponseCallback(this, callfuncND_selector(HelloWorld::okHttpRequestCompleted));
        request->setTag("ok");
        cocos2d::extension::CCHttpClient::getInstance()->send(request);
        request->release();
    }
    

}



void HelloWorld::getNetworks()
{
    //clear the number in the poker
    _pLeftPoker->setString("");
    _pRightPoker->setString("");
    
    //get the win times from the server
    cocos2d::extension::CCHttpRequest* request = new cocos2d::extension::CCHttpRequest();
    
    std::string str1 = "http://localhost/info.php?";
    std::string str2 = str1+"password="+"12345";
    request->setUrl(str2.c_str());
    request->setRequestType(cocos2d::extension::CCHttpRequest::kHttpGet);
    request->setResponseCallback(this, callfuncND_selector(HelloWorld::getHttpRequestCompleted));
    request->setTag("ok");
    cocos2d::extension::CCHttpClient::getInstance()->send(request);
    request->release();
    
}


// networks callback
void HelloWorld::getHttpRequestCompleted(cocos2d::CCNode *sender ,void *data)
{
    //get and printf the score
    cocos2d::extension::CCHttpResponse *response = (cocos2d::extension::CCHttpResponse*)data;
    if (!response)
    {
        printf("network is feild!\n");
        return;
    }
    std::vector<char> *buffer = response->getResponseData();
    
    std::string recieveData;
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        recieveData += (*buffer)[i];
        printf("%c", (*buffer)[i]);
    }
    
    recieveData = "Your Win times:" + recieveData;
    _pWins->setString(recieveData.c_str());
    
    printf("\n");
    
    
}
void HelloWorld::okHttpRequestCompleted(cocos2d::CCNode *sender ,void *data)
{
    // do nothing but server did update the score
    cocos2d::extension::CCHttpResponse *response = (cocos2d::extension::CCHttpResponse*)data;
    if (!response)
    {
        printf("network is feild!\n");
        return;
    }
   }
// CardSprite callback methods

void HelloWorld::flipLeftCard(cocos2d::CCNode *sender)
{
    printf("action\n");
    
    //display the number in the poker
    char *temp = new char[64];
    sprintf(temp, "%d",_myNumber);
    
    if (_myNumber <= 9) {
        
        _pLeftPoker->setString(temp);
        
    }
    else if (_myNumber <= 99)
    {
        
        _pLeftPoker->setString(temp);
    }
    else
    {
        
        _pLeftPoker->setString(temp);
    }

}

void HelloWorld::flipRightCard(cocos2d::CCNode *sender)
{
     printf("action1\n");
    
    
    //display the number in the poker
    char *temp = new char[64];
    sprintf(temp, "%d",_compuerNumber);
    if (_compuerNumber <= 9) {
        

        _pRightPoker->setString(temp);
    }
    else if (_compuerNumber <= 99)
    {
        
         _pRightPoker->setString(temp);
    }
    else
    {
        
         _pRightPoker->setString(temp);
    }

}


//touch event methods

void HelloWorld::registerWithTouchDispatcher(){
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    
    return true;
}
void HelloWorld::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
   
}
void HelloWorld::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
    
    // to find witch sprite is choosed 
    CCSprite *pget = (CCSprite*)this->getChildByTag(GETTAG);
    CCSprite *pok  = (CCSprite*)this->getChildByTag(OKTAG);
    
    CCPoint touchPoint=convertTouchToNodeSpace(pTouch);
    
    
    if (pget->boundingBox().containsPoint(touchPoint)) {
        printf("get touch!\n");
        this->getNetworks();
    }
    
    if (pok->boundingBox().containsPoint(touchPoint)) {
        printf("ok touch!\n");
        this->okNetworks();
    }
    
}
void HelloWorld::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    
}
