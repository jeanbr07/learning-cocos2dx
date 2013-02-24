//
//  GameCharacter.cc
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-24.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "GameCharacter.h"

#define CC_IS_IPAD() (CCDirector::sharedDirector()->getWinSize().width == 1024 || CCDirector::sharedDirector()->getWinSize().width == 2048)

using namespace cocos2d;

int GameCharacter::getWeaponDamage() {
  // Default to zero damage
  CCLOG("getWeaponDamage should be overridden");
  return 0;
}

void GameCharacter::checkAndClampSpritePosition() {
  CCPoint currentSpritePosition = this->getPosition();
  if (CC_IS_IPAD()) {
    // Clamp for the iPad
    if (currentSpritePosition.x < 30.0f) {
      this->setPosition(ccp(30.0f, currentSpritePosition.y));
    } else if (currentSpritePosition.x > 1000.0f) {
      this->setPosition(ccp(1000.0f, currentSpritePosition.y));
    }
  } else {
    if (currentSpritePosition.x < 24.0f) {
      this->setPosition(ccp(24.0f, currentSpritePosition.y));
    } else if (currentSpritePosition.x > 456.0f) {
      this->setPosition(ccp(456.0f, currentSpritePosition.y));
    }
  }
}
