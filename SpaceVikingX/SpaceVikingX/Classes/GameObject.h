//
//  GameObject.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-24.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#ifndef __SpaceVikingX__GameObject__
#define __SpaceVikingX__GameObject__

#include <iostream>
#include "cocos2d.h"
#include "Constants.h"
#include "CommonProtocols.h"

class GameObject : public cocos2d::CCSprite
{
public:
  virtual bool init();
  
  virtual void changeState(CharacterStates newState);
  virtual void updateState(float deltaTime, cocos2d::CCArray *gameObjects);
  virtual cocos2d::CCRect adjustedBoundingBox();
  cocos2d::CCAnimation * loadPlistForAnimation(const char *animationName, const char *className);
  
protected:
  bool isActive_;
  bool reactsToScreenBoundaries_;
  cocos2d::CCSize screenSize_;
  GameObjectType gameObjectType_;
};

#endif /* defined(__SpaceVikingX__GameObject__) */
