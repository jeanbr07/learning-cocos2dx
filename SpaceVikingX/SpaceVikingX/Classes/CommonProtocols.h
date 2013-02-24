//
//  CommonProtocols.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-24.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "cocos2d.h"

#ifndef SpaceVikingX_CommonProtocols_h
#define SpaceVikingX_CommonProtocols_h

typedef enum {
  kDirectionLeft,
  kDirectionRight
} PhaserDirection;

typedef enum {
  kStateSpawning,
  kStateIdle,
  kStateCrouching,
  kStateStandingUp,
  kStateWalking,
  kStateAttacking,
  kStateJumping,
  kStateBreathing,
  kStateTakingDamage,
  kStateDead,
  kStateTraveling,
  kStateRotating,
  kStateDrilling,
  kStateAfterJumping
} CharacterStates;

typedef enum {
  kObjectTypeNone,
  kPowerUpTypeHealth,
  kPowerUpTypeMallet,
  kEnemyTypeRadarDish,
  kEnemyTypeSpaceCargoShip,
  kEnemyTypeAlienRobot,
  kEnemyTypePhaser,
  kVikingType,
  kSkullType,
  kRockType,
  kMeteorType,
  kFrozenVikingType,
  kIceType,
  kLongBlockType,
  kCartType,
  kSpikesType,
  kDiggerType,
  kGroundType
} GameObjectType;

class GameplayLayerDelegate
{
  virtual void createObjectOfType(GameObjectType objectType,
                                  int initialHealth,
                                  const cocos2d::CCPoint& spawnLocation,
                                  int zValue);
  virtual void createPhaserWithDirection(PhaserDirection phaserDirection,
                                         const cocos2d::CCPoint& spawnPosition);
};

#endif
