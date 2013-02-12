//
//  GameplayLayer.cpp
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-11.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "GameplayLayer.h"

using namespace cocos2d;

bool GameplayLayer::init()
{
  if (!CCLayer::init()) {
    return false;
  }

  this->setTouchEnabled(true);

  CCSize size = CCDirector::sharedDirector()->getWinSize();
  vikingSprite = CCSprite::create("sv_anim_1.png");
  vikingSprite->setPosition(ccp(size.width/2, size.height*0.17f));

  // If NOT on the iPad, scale down
  if (size.width == 480) {
    // FIXME: this doesn't seem quite correct...
    vikingSprite->setScaleX(480 / 1024.0f);
    vikingSprite->setScaleY(320 / 768.0f);
  }

  this->addChild(vikingSprite, 0);

  return true;
}
