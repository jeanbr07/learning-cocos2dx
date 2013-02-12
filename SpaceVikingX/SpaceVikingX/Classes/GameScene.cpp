//
//  GameScene.cpp
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-11.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "GameScene.h"

#include "BackgroundLayer.h"
#include "GameplayLayer.h"

bool GameScene::init()
{
  if (!CCScene::init()) {
    return false;
  }

  BackgroundLayer *backgroundLayer = BackgroundLayer::create();
  GameplayLayer *gameplayLayer = GameplayLayer::create();

  this->addChild(backgroundLayer, 0);
  this->addChild(gameplayLayer, 5);
  
  return true;
}
