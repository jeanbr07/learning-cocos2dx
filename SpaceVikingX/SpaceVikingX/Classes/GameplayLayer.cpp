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

  screenSize_ = CCDirector::sharedDirector()->getWinSize();

  // Sprites! (book page 52)
  CCSpriteFrameCache *spriteCache = CCSpriteFrameCache::sharedSpriteFrameCache();
  if (CC_IS_IPAD()) {
    spriteCache->addSpriteFramesWithFile("scene1atlas.plist", "scene1atlas.png");
    sceneSpriteBatchNode_ = CCSpriteBatchNode::create("scene1atlas.png");
  } else {
    spriteCache->addSpriteFramesWithFile("scene1atlasiPhone.plist", "scene1atlasiPhone.png");
    sceneSpriteBatchNode_ = CCSpriteBatchNode::create("scene1atlasiPhone.png");
  }

  vikingSprite_ = CCSprite::createWithSpriteFrameName("sv_anim_1.png");
  sceneSpriteBatchNode_->addChild(vikingSprite_);
  this->addChild(sceneSpriteBatchNode_);
  
  vikingSprite_->setPosition(ccp(screenSize_.width/2, screenSize_.height*0.17f));

  // If NOT on the iPad, scale down
  if (screenSize_.width == 480) {
    // FIXME: this doesn't seem quite correct...
    vikingSprite_->setScaleX(480 / 1024.0f);
    vikingSprite_->setScaleY(320 / 768.0f);
  }

  this->createObject(kEnemyTypeRadarDish, 100, ccp(screenSize_.width * 0.878f, screenSize_.height * 0.13f), 10);
  
  this->initJoystickAndButtons();
  this->scheduleUpdate();

  return true;
}

void GameplayLayer::initJoystickAndButtons()
{
  CCRect joystickBaseDimensions = CCRectMake(0, 0, 128.0f, 128.0f);
  CCRect jumpButtonDimensions = CCRectMake(0, 0, 64.0f, 64.0f);
  CCRect attackButtonDimensions = CCRectMake(0, 0, 64.0f, 64.0f);

  CCPoint joystickBasePosition, jumpButtonPosition, attackButtonPosition;

  if (CC_IS_IPAD()) {
    joystickBasePosition = ccp(screenSize_.width*0.0625f,
                               screenSize_.height*0.052f);
    jumpButtonPosition = ccp(screenSize_.width*0.946f,
                             screenSize_.height*0.052f);
    attackButtonPosition = ccp(screenSize_.width*0.947f,
                               screenSize_.height*0.169f);
  } else {
    joystickBasePosition = ccp(screenSize_.width*0.07f,
                               screenSize_.height*0.11f);
    jumpButtonPosition = ccp(screenSize_.width*0.93f,
                             screenSize_.height*0.11f);
    attackButtonPosition = ccp(screenSize_.width*0.93f,
                               screenSize_.height*0.35f);
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

void GameplayLayer::createObject(GameObjectType objectType, int initialHealth, cocos2d::CCPoint spawnLocation, int zValue)
{
  if (objectType == kEnemyTypeRadarDish) {
    CCLOG("Creating the Radar Enemy");
    RadarDish *radarDish = RadarDish::create();
    radarDish->setCharacterHealth(initialHealth);
    radarDish->setPosition(spawnLocation);
    sceneSpriteBatchNode_->addChild(radarDish, zValue, kRadarDishTagValue);
  }
}

void GameplayLayer::createPhaser(PhaserDirection phaserDirection, CCPoint spawnPosition) {
  CCLOG("Placeholder for Chapter 5, see below");
  return;
}

#define SET_BOUND_INSIDE(x, min, max) x = (x < min ? min : (x > max ? max : x))

void GameplayLayer::applyJoystick(SneakyJoystick *aJoystick, CCNode *toNode, float deltaTime)
{
  CCPoint scaledVelocity = ccpMult(aJoystick->getVelocity(), screenSize_.width);
  CCPoint newPosition = ccp(toNode->getPosition().x + scaledVelocity.x * deltaTime,
                            toNode->getPosition().y + scaledVelocity.y * deltaTime);

  SET_BOUND_INSIDE(newPosition.x, 0, screenSize_.width);
  SET_BOUND_INSIDE(newPosition.y, 0, screenSize_.height);

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
  CCArray *gameObjects = sceneSpriteBatchNode_->getChildren();

  for (int i = 0; i < gameObjects->count(); i++) {
    GameCharacter *tempChar = (GameCharacter *)gameObjects->objectAtIndex(i);
    tempChar->updateState(deltaTime, *gameObjects);
  }

  this->applyJoystick(leftJoystick_, vikingSprite_, deltaTime);
}


