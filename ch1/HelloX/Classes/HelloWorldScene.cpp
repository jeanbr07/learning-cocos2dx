#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene() {
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
bool HelloWorld::init() {
  if (!CCLayer::init()) {
    return false;
  }

  CCSize windowSize = CCDirector::sharedDirector()->getWinSize();

  CCLabelTTF* pLabel = CCLabelTTF::create("Hello cocos2d-x!", "Thonburi", 48);
  pLabel->setPosition(ccp(windowSize.width / 2, windowSize.height - 36));
  this->addChild(pLabel);

  CCSprite *spaceCargoShip = CCSprite::create("SpaceCargoShip.png");
  spaceCargoShip->setPosition(ccp(windowSize.width/2, windowSize.height/2));
  this->addChild(spaceCargoShip);

  CCMoveTo *movement = CCMoveTo::create(5.0, ccp(0, windowSize.height/2));
  spaceCargoShip->runAction(movement);
  
  return true;
}
