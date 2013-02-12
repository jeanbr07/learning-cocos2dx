//
//  SpaceVikingXAppDelegate.cpp
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-09.
//  Copyright Ferocious Apps 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
  // initialize director
  CCDirector *pDirector = CCDirector::sharedDirector();
  pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

  CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
  std::vector<std::string> searchPaths;
  if (CCDirector::sharedDirector()->getWinSize().width == 1024 || CCDirector::sharedDirector()->getWinSize().width == 2048) {
    // NOTE: we don't have retina assets for iPad. If we did, another else if
    // condition would probably be useful here.
    pEGLView->setDesignResolutionSize(1024, 768, kResolutionNoBorder);
    pDirector->setContentScaleFactor(1.0);
    searchPaths.push_back("ipad");
  } else {
    pEGLView->setDesignResolutionSize(480, 320, kResolutionNoBorder);
    pDirector->setContentScaleFactor(1.0);
    searchPaths.push_back("iphone");
  }
  CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(searchPaths);

  // turn on display FPS
  pDirector->setDisplayStats(true);

  // set FPS. the default value is 1.0/60 if you don't call this
  pDirector->setAnimationInterval(1.0 / 60);

  // run our main GameScene
  pDirector->runWithScene(GameScene::create());

  return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
  CCDirector::sharedDirector()->stopAnimation();
  SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
  SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
  CCDirector::sharedDirector()->startAnimation();
  SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
  SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
