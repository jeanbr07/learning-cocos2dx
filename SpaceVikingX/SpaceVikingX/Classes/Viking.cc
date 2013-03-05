//
//  Viking.cc
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-26.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "Viking.h"

using namespace cocos2d;

bool Viking::isCarryingWeapon()
{
  return this->isCarryingMallet_;
}

int Viking::getWeaponDamage()
{
  if (this->isCarryingMallet_) {
    return kVikingMalletDamage;
  }
  return kVikingFistDamage;
}

void Viking::applyJoystick(SneakyJoystick *joystick, float deltaTime)
{
  CCPoint scaledVelocity = ccpMult(joystick->getVelocity(), 128.0f);
  CCPoint oldPosition = this->getPosition();
  CCPoint newPosition = ccp(oldPosition.x + scaledVelocity.x * deltaTime, oldPosition.y);

  this->setPosition(newPosition);

  if (oldPosition.x > newPosition.x) {
    this->setFlipX(true);
  } else {
    this->setFlipX(false);
  }

}

void Viking::checkAndClampSpritePosition()
{
  if (this->characterState_ != kStateJumping) {
    if (this->getPositionY() > 110.0f)
      this->setPosition(ccp(this->getPositionX(), 110.0f));
  }

  GameCharacter::checkAndClampSpritePosition();
}

void Viking::changeState(CharacterStates newState)
{
  this->stopAllActions();

  CCAction *action = NULL;
  CCAction *movementAction = NULL;
  CCPoint newPosition;

  this->setCharacterState(newState);

  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

  switch (newState) {
    case kStateIdle: {
      if (isCarryingMallet_) {
        this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sv_mallet_1.png"));
      } else {
        this->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("sv_anim_1.png"));
      }
      break;
    }
    case kStateWalking: {
      if (isCarryingMallet_) {
        action = CCAnimate::create(walkingMalletAnim_);
      } else {
        action = CCAnimate::create(walkingAnim_);
      }
      break;
    }
    case kStateCrouching: {
      if (isCarryingMallet_) {
        action = CCAnimate::create(crouchingMalletAnim_);
      } else {
        action = CCAnimate::create(crouchingAnim_);
      }
      break;
    }
    case kStateStandingUp: {
      if (isCarryingMallet_) {
        action = CCAnimate::create(standingUpMalletAnim_);
      } else {
        action = CCAnimate::create(standingUpAnim_);
      }
      break;
    }
    case kStateBreathing: {
      if (isCarryingMallet_) {
        action = CCAnimate::create(breathingMalletAnim_);
      } else {
        action = CCAnimate::create(breathingAnim_);
      }
      break;
    }
    case kStateJumping: {
      newPosition = ccp(screenSize.width * 0.2f, 0.0f);
      if (this->isFlipX()) {
        newPosition = ccp(newPosition.x * -1.0f, 0.0f);
      }
      movementAction = CCJumpBy::create(0.5f, newPosition, 160.0f, 1);

      if (isCarryingMallet_) {
        CCArray *spawnList = CCArray::create(CCAnimate::create(jumpingMalletAnim_), movementAction);
        CCArray *actionList = CCArray::create(CCAnimate::create(crouchingMalletAnim_), spawnList, afterJumpingMalletAnim_);
        action = CCSequence::create(actionList);
      } else {
        CCArray *spawnList = CCArray::create(CCAnimate::create(jumpingAnim_), movementAction);
        CCArray *actionList = CCArray::create(CCAnimate::create(crouchingAnim_), spawnList, afterJumpingAnim_);
        action = CCSequence::create(actionList);
      }
      break;
    }
    case kStateAttacking: {
      if (isCarryingMallet_) {
        action = CCAnimate::create(malletPunchAnim_);
      } else {
        if (kLeftHook == myLastPunch_) {
          myLastPunch_ = kRightHook;
          action = CCAnimate::create(rightPunchAnim_);
        } else {
          myLastPunch_ = kLeftHook;
          action = CCAnimate::create(leftPunchAnim_);
        }
      }
      break;
    }
    case kStateTakingDamage: {
      this->characterHealth_ -= 10.0f;
      action = CCAnimate::create(phaserShockAnim_);
      break;
    }
    case kStateDead: {
      action = CCAnimate::create(deathAnim_);
      break;
    }
    default: {
      break;
    }
  }

  if (!action) {
    this->runAction(action);
  }
}

void Viking::updateState(float deltaTime, cocos2d::CCArray *gameObjects)
{
  if (this->characterState_ == kStateDead) {
    return;
  }

  if (this->characterState_ == kStateTakingDamage && this->numberOfRunningActions() > 0) {
    return;
  }

  CCRect myBoundingBox = this->adjustedBoundingBox();

  for (int i = 0; i < gameObjects->count(); i++) {
    GameCharacter *character = (GameCharacter *)gameObjects->objectAtIndex(i);
    if (character->getTag() == kVikingSpriteTagValue) continue;

    CCRect characterBox = character->adjustedBoundingBox();
    if (characterBox.intersectsRect(myBoundingBox)) {
      // TODO handle collisions
    }
  }

  this->checkAndClampSpritePosition();

  if (this->characterState_ == kStateIdle || this->characterState_ == kStateWalking || this->characterState_ == kStateCrouching || this->characterState_ == kStateStandingUp || this->characterState_ == kStateBreathing) {
    if (jumpButton_->getIsActive()) {
      this->changeState(kStateJumping);
    } else if (attackButton_->getIsActive()) {
      this->changeState(kStateAttacking);
    } else if (joystick_->getVelocity().x == 0.0 && joystick_->getVelocity().y == 0.0) {
      if (this->characterState_ == kStateCrouching) {
        this->changeState(kStateStandingUp);
      }
    } else if (joystick_->getVelocity().y < -0.45f) {
      if (this->characterState_ != kStateCrouching) {
        this->changeState(kStateCrouching);
      }
    } else if (joystick_->getVelocity().x != 0.0f) { // dpad moving
      if (this->characterState_ != kStateWalking) {
        this->changeState(kStateWalking);
      }
      this->applyJoystick(joystick_, deltaTime);
    }
  }

  if (this->numberOfRunningActions() == 0) {
    if (this->characterHealth_ <= 0.0f) {
      this->changeState(kStateDead);
    } else if (this->characterState_ == kStateIdle) {
      millisecondsStayingIdle_ += deltaTime;
      if (millisecondsStayingIdle_ > kVikingIdleTimer) {
        this->changeState(kStateBreathing);
      }
    } else if (this->characterState_ != kStateCrouching && this->characterState_ != kStateIdle) {
      millisecondsStayingIdle_ = 0.0;
      this->changeState(kStateIdle);
    }
  }
}

cocos2d::CCRect Viking::adjustedBoundingBox()
{
  // Adjust the bouding box to the size of the sprite
  // without the transparent space
  CCRect vikingBoundingBox = this->boundingBox();
  float xOffset;
  float xCropAmount = vikingBoundingBox.size.width * 0.5482f;
  float yCropAmount = vikingBoundingBox.size.height * 0.095f;

  if (this->isFlipX()) {
    // Viking is facing to the left; back is facing right
    xOffset = vikingBoundingBox.size.width * 0.4217f;
  } else {
    // Viking is facing to the rigth, back is on the left
    xOffset = vikingBoundingBox.size.width * 0.1566f;
  }
  vikingBoundingBox = CCRectMake(vikingBoundingBox.origin.x + xOffset,
                                 vikingBoundingBox.origin.y,
                                 vikingBoundingBox.size.width - xCropAmount,
                                 vikingBoundingBox.size.height - yCropAmount);
  if (this->characterState_ == kStateCrouching) {
    // Shrink the bounding box to 56% of height
    // 88 pixels on top on iPad
    vikingBoundingBox = CCRectMake(vikingBoundingBox.origin.x,
                                   vikingBoundingBox.origin.y,
                                   vikingBoundingBox.size.width,
                                   vikingBoundingBox.size.height * 0.56f);
  }

  return vikingBoundingBox;
}
