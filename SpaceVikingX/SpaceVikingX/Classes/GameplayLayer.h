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

class GameplayLayer : public cocos2d::CCLayer
{
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(GameplayLayer);

private:
  cocos2d::CCSprite *vikingSprite;
};

#endif /* defined(__SpaceVikingX__GameplayLayer__) */
