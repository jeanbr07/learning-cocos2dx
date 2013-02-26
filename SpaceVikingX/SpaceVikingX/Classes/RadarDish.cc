//
//  RadarDish.cc
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-26.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "RadarDish.h"

using namespace cocos2d;

bool RadarDish::init()
{
  if (!GameObject::init()) {
    return false;
  }

  CCLOG("### RadarDish initialized");
  this->initAnimations();
  this->characterHealth_ = 100.0f;
  this->gameObjectType_ = kEnemyTypeRadarDish;
  this->changeState(kStateSpawning);
  return true;
}

void RadarDish::changeState(CharacterStates newState) {
  this->stopAllActions();
  CCAction *action = NULL;
  this->setCharacterState(newState);

  switch (newState) {
    case kStateSpawning: {
      CCLOG("RadarDish->Starting the Spawning Animation");
      action = CCAnimate::create(tiltingAnim_);
      break;
    }
    case kStateIdle: {
      CCLOG("RadarDish->Changing State to Idle");
      action = CCAnimate::create(transmittingAnim_);
      break;
    }
    case kStateTakingDamage: {
      CCLOG("RadarDish->Changing State to TakingDamage");
      characterHealth_ = characterHealth_ - vikingCharacter_->getWeaponDamage();
      if (characterHealth_ <= 0) {
        this->changeState(kStateDead);
      } else {
        action = CCAnimate::create(takingAHitAnim_);
      }
      break;
    }
    case kStateDead: {
      CCLOG("RadarDish->Changing State to Dead");
      action = CCAnimate::create(blowingUpAnim_);
      break;
    }
    default: {
      CCLOG("Unhandled state %d in RadarDish", newState);
      break;
    }
  }

  if (action) {
    this->runAction(action);
  }
}

void RadarDish::updateState(cocos2d::CCTime deltaTime, const cocos2d::CCArray& listOfGameObjects)
{
  if (characterState_ == kStateDead) return;

  vikingCharacter_ = (GameCharacter *)this->getParent()->getChildByTag(kVikingSpriteTagValue);
  CharacterStates vikingState = vikingCharacter_->getCharacterState();
  CCRect vikingBoundingBox = vikingCharacter_->adjustedBoundingBox();

  if ((vikingState == kStateAttacking) && this->adjustedBoundingBox().intersectsRect(vikingBoundingBox)) {
    if (characterState_ != kStateTakingDamage) {
      this->changeState(kStateTakingDamage);
      return;
    }
  }

  if (this->numberOfRunningActions() == 0 && characterState_ != kStateDead) {
    CCLOG("Going to idle");
    this->changeState(kStateIdle);
    return;
  }
}

void RadarDish::initAnimations()
{
  this->tiltingAnim_ = this->loadPlistForAnimation("tiltingAnim", "RadarDish");
  this->transmittingAnim_ = this->loadPlistForAnimation("transmittingAnim", "RadarDish");
  this->takingAHitAnim_ = this->loadPlistForAnimation("takingAHitAnim", "RadarDish");
  this->blowingUpAnim_ = this->loadPlistForAnimation("blowingUpAnim", "RadarDish");
}


