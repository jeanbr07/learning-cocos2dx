//
//  GameCharacter.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-24.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#ifndef __SpaceVikingX__GameCharacter__
#define __SpaceVikingX__GameCharacter__

#include <iostream>
#include "cocos2d.h"
#include "GameObject.h"

class GameCharacter : public GameObject {
protected:
  int characterHealth_;
  CharacterStates characterState_;

public:
  void checkAndClampSpritePosition();
  int getWeaponDamage();

  CharacterStates getCharacterState();
  void setCharacterState(CharacterStates newState);
  int getCharacterHealth();
  void setCharacterHealth(int newHealth);
};

#endif /* defined(__SpaceVikingX__GameCharacter__) */
