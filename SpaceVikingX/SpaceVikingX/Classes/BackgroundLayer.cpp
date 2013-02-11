//
//  BackgroundLayer.cpp
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-09.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "BackgroundLayer.h"

using namespace cocos2d;

CCScene* BackgroundLayer::scene()
{
  CCScene *scene = CCScene::create();
  BackgroundLayer *layer = BackgroundLayer::create();

  scene->addChild(layer);

  return scene;
}

bool BackgroundLayer::init()
{
  if (!CCLayer::init()) {
    return false;
  }

  CCSprite* pSprite = CCSprite::create("images/background.png");

  // we want the background right in the center
  CCSize size = CCDirector::sharedDirector()->getWinSize();
  pSprite->setPosition( ccp(size.width/2, size.height/2) );

  this->addChild(pSprite, 0);

  return true;
}
