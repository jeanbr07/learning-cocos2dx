//
//  GameplayLayer.cpp
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-11.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "GameplayLayer.h"

#define CC_IS_IPAD() (CCDirector::sharedDirector()->getWinSize().width == 1024 || CCDirector::sharedDirector()->getWinSize().width == 2048)

using namespace cocos2d;

bool GameplayLayer::init()
{
  if (!CCLayer::init()) {
    return false;
  }

  this->setTouchEnabled(true);

  CCSize size = CCDirector::sharedDirector()->getWinSize();
  vikingSprite_ = CCSprite::create("sv_anim_1.png");
  vikingSprite_->setPosition(ccp(size.width/2, size.height*0.17f));

  // If NOT on the iPad, scale down
  if (size.width == 480) {
    // FIXME: this doesn't seem quite correct...
    vikingSprite_->setScaleX(480 / 1024.0f);
    vikingSprite_->setScaleY(320 / 768.0f);
  }

  this->addChild(vikingSprite_, 0);

  this->initJoystickAndButtons();
  this->scheduleUpdate();

  return true;
}

void GameplayLayer::initJoystickAndButtons()
{
  CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
  CCRect joystickBaseDimensions = CCRectMake(0, 0, 128.0f, 128.0f);
  CCRect jumpButtonDimensions = CCRectMake(0, 0, 64.0f, 64.0f);
  CCRect attackButtonDimensions = CCRectMake(0, 0, 64.0f, 64.0f);

  CCPoint joystickBasePosition, jumpButtonPosition, attackButtonPosition;

  if (CC_IS_IPAD()) {
    joystickBasePosition = ccp(screenSize.width*0.0625f,
                               screenSize.height*0.052f);
    jumpButtonPosition = ccp(screenSize.width*0.946f,
                             screenSize.height*0.052f);
    attackButtonPosition = ccp(screenSize.width*0.947f,
                               screenSize.height*0.169f);
  } else {
    joystickBasePosition = ccp(screenSize.width*0.07f,
                               screenSize.height*0.11f);
    jumpButtonPosition = ccp(screenSize.width*0.93f,
                             screenSize.height*0.11f);
    attackButtonPosition = ccp(screenSize.width*0.93f,
                               screenSize.height*0.35f);
  }

  SneakyJoystickSkinnedBase *joystickBase = SneakyJoystickSkinnedBase::create();
  joystickBase->setPosition(joystickBasePosition);
  joystickBase->setBackgroundSprite(CCSprite::create("dpadDown.png"));
  joystickBase->setThumbSprite(CCSprite::create("joystickDown.png"));

  leftJoystick_ = new SneakyJoystick;
  leftJoystick_->initWithRect(joystickBaseDimensions);
  joystickBase->setJoystick(leftJoystick_);
  this->addChild(joystickBase);

  SneakyButtonSkinnedBase *jumpButtonBase = SneakyButtonSkinnedBase::create();
  jumpButtonBase->setPosition(jumpButtonPosition);
  jumpButtonBase->setDefaultSprite(CCSprite::create("jumpUp.png"));
  jumpButtonBase->setActivatedSprite(CCSprite::create("jumpDown.png"));
  jumpButtonBase->setPressSprite(CCSprite::create("jumpDown.png"));

  jumpButton_ = new SneakyButton;
  jumpButton_->initWithRect(jumpButtonDimensions);
  jumpButton_->setIsToggleable(false);
  jumpButtonBase->setButton(jumpButton_);
  this->addChild(jumpButtonBase);

  SneakyButtonSkinnedBase *attackButtonBase = SneakyButtonSkinnedBase::create();
  attackButtonBase->setPosition(attackButtonPosition);
  attackButtonBase->setDefaultSprite(CCSprite::create("handUp.png"));
  attackButtonBase->setActivatedSprite(CCSprite::create("handDown.png"));
  attackButtonBase->setPressSprite(CCSprite::create("handDown.png"));

  attackButton_ = new SneakyButton;
  attackButton_->initWithRect(attackButtonDimensions);
  attackButton_->setIsToggleable(false);
  attackButtonBase->setButton(attackButton_);
  this->addChild(attackButtonBase);

}

void GameplayLayer::applyJoystick(SneakyJoystick *aJoystick, CCNode *toNode, float deltaTime)
{
  CCPoint scaledVelocity = ccpMult(aJoystick->getVelocity(), 1024.0f);
  CCPoint newPosition = ccp(toNode->getPosition().x + scaledVelocity.x * deltaTime,
                            toNode->getPosition().y + scaledVelocity.y * deltaTime);
  toNode->setPosition(newPosition);

  if (jumpButton_->getIsActive()) {
    CCLOG("Jump button is pressed!");
  }
  if (attackButton_->getIsActive()) {
    CCLOG("Attack button is pressed!");
  }
}

void GameplayLayer::update(float deltaTime)
{
  this->applyJoystick(leftJoystick_, vikingSprite_, deltaTime);
}


