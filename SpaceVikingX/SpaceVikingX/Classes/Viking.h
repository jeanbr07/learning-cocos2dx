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
  void initAnimations();
  cocos2d::CCRect adjustedBoundingBox();

  bool isCarryingWeapon();
  int getWeaponDamage();
  void applyJoystick(SneakyJoystick *joystick, float deltaTime);
  void checkAndClampSpritePosition();
  void changeState(CharacterStates newState);
  void updateState(float deltaTime, cocos2d::CCArray *gameObjects);

  SneakyJoystick * getJoystick();
  void setJoystick(SneakyJoystick *aJoystick);
  SneakyButton * getJumpButton();
  void setJumpButton(SneakyButton *aButton);
  SneakyButton * getAttackButton();
  void setAttackButton(SneakyButton *aButton);

protected:
  LastPunchType myLastPunch_;
  bool isCarryingMallet_;
  cocos2d::CCSpriteFrame *standingFrame_;

  // Standing, breathing, and walking
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, breathingAnim_, BreathingAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, breathingMalletAnim_, BreathingMalletAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, walkingAnim_, WalkingAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, walkingMalletAnim_, WalkingMalletAnim)

  // Crouching, standing up, and Jumping
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, crouchingAnim_, CrouchingAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, crouchingMalletAnim_, CrouchingMalletAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, standingUpAnim_, StandingUpAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, standingUpMalletAnim_, StandingUpMalletAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, jumpingAnim_, JumpingAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, jumpingMalletAnim_, JumpingMalletAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, afterJumpingAnim_, AfterJumpingAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, afterJumpingMalletAnim_, AfterJumpingMalletAnim)

  // Punching
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, rightPunchAnim_, RightPunchAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, leftPunchAnim_, LeftPunchAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, malletPunchAnim_, MalletPunchAnim)

  // Taking Damage and Death
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, phaserShockAnim_, PhaserShockAnim)
  CC_SYNTHESIZE_RETAIN(cocos2d::CCAnimation*, deathAnim_, DeathAnim)

  SneakyJoystick *joystick_;
  SneakyButton *jumpButton_;
  SneakyButton *attackButton_;

  float millisecondsStayingIdle_;
};

#endif /* defined(__SpaceVikingX__Viking__) */
