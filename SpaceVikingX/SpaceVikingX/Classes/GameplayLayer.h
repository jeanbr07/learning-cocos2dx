//
//  GameplayLayer.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-11.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#ifndef __SpaceVikingX__GameplayLayer__
#define __SpaceVikingX__GameplayLayer__

#include "cocos2d.h"

#include "SneakyJoystick.h"
#include "SneakyButton.h"
#include "SneakyButtonSkinnedBase.h"
#include "SneakyJoystickSkinnedBase.h"

class GameplayLayer : public cocos2d::CCLayer
{
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(GameplayLayer);
  void update(float deltaTime);

private:
  void initJoystickAndButtons();
  void applyJoystick(SneakyJoystick *aJoystick, CCNode *toNode, float deltaTime);
  
  cocos2d::CCSprite *vikingSprite_;
  SneakyJoystick *leftJoystick_;
  SneakyButton *jumpButton_;
  SneakyButton *attackButton_;
};

#endif /* defined(__SpaceVikingX__GameplayLayer__) */
