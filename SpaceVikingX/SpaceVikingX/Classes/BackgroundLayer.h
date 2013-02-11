//
//  BackgroundLayer.h
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-09.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#ifndef __SpaceVikingX__BackgroundLayer__
#define __SpaceVikingX__BackgroundLayer__

#include "cocos2d.h"

class BackgroundLayer : public cocos2d::CCLayer
{
public:
  virtual bool init();
  static cocos2d::CCScene* scene();
  CREATE_FUNC(BackgroundLayer);
};

#endif /* defined(__SpaceVikingX__BackgroundLayer__) */
