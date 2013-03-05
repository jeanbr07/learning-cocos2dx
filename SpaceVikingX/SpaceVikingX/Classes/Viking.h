//
//  Viking.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-26.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#ifndef __SpaceVikingX__Viking__
#define __SpaceVikingX__Viking__

#include <iostream>
#include "cocos2d.h"
#include "GameCharacter.h"
#include "SneakyButton.h"
#include "SneakyJoystick.h"

typedef enum {
  kLeftHook,
  kRightHook
} LastPunchType;

class Viking : public GameCharacter {
public:
  virtual bool init();
  CREATE_FUNC(Viking);
  cocos2d::CCRect adjustedBoundingBox();

  bool isCarryingWeapon();
  int getWeaponDamage();
  void applyJoystick(SneakyJoystick *joystick, float deltaTime);
  void checkAndClampSpritePosition();
  void changeState(CharacterStates newState);
  void updateState(float deltaTime, cocos2d::CCArray *gameObjects);

protected:
  LastPunchType myLastPunch_;
  bool isCarryingMallet_;
  cocos2d::CCSpriteFrame *standingFrame_;

  // Standing, breathing, and walking
  cocos2d::CCAnimation *breathingAnim_;
  cocos2d::CCAnimation *breathingMalletAnim_;
  cocos2d::CCAnimation *walkingAnim_;
  cocos2d::CCAnimation *walkingMalletAnim_;

  // Crouching, standing up, and Jumping
  cocos2d::CCAnimation *crouchingAnim_;
  cocos2d::CCAnimation *crouchingMalletAnim_;
  cocos2d::CCAnimation *standingUpAnim_;
  cocos2d::CCAnimation *standingUpMalletAnim_;
  cocos2d::CCAnimation *jumpingAnim_;
  cocos2d::CCAnimation *jumpingMalletAnim_;
  cocos2d::CCAnimation *afterJumpingAnim_;
  cocos2d::CCAnimation *afterJumpingMalletAnim_;

  // Punching
  cocos2d::CCAnimation *rightPunchAnim_;
  cocos2d::CCAnimation *leftPunchAnim_;
  cocos2d::CCAnimation *malletPunchAnim_;

  // Taking Damage and Death
  cocos2d::CCAnimation *phaserShockAnim_;
  cocos2d::CCAnimation *deathAnim_;
  SneakyJoystick *joystick_;
  SneakyButton *jumpButton_;
  SneakyButton *attackButton_;

  float millisecondsStayingIdle_;
};

#endif /* defined(__SpaceVikingX__Viking__) */
