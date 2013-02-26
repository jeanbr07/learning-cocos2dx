//
//  RadarDish.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-26.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#ifndef __SpaceVikingX__RadarDish__
#define __SpaceVikingX__RadarDish__

#include <iostream>
#include "cocos2d.h"
#include "GameCharacter.h"

class RadarDish : public GameCharacter {
public:
  virtual bool init();

protected:
  void initAnimations();
  void changeState(CharacterStates newState);
  void updateState(cocos2d::CCTime deltaTime, const cocos2d::CCArray& listOfGameObjects);

  cocos2d::CCAnimation *tiltingAnim_;
  cocos2d::CCAnimation *transmittingAnim_;
  cocos2d::CCAnimation *takingAHitAnim_;
  cocos2d::CCAnimation *blowingUpAnim_;
  GameCharacter *vikingCharacter_;

};

#endif /* defined(__SpaceVikingX__RadarDish__) */
