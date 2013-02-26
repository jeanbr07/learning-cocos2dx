//
//  GameObject.cpp
//  SpaceVikingX
//
//  Created by Greg Heo on 2013-02-24.
//  Copyright (c) 2013 Ferocious Apps. All rights reserved.
//

#include "GameObject.h"
#include "CCFileUtilsIOS.h"

static void str_split(std::string src, const char* token, std::vector<std::string>& vect)
{
  int nend=0;
  int nbegin=0;
  while(nend != -1)
  {
    nend = src.find(token, nbegin);
    if(nend == -1)
      vect.push_back(src.substr(nbegin, src.length()-nbegin));
    else
      vect.push_back(src.substr(nbegin, nend-nbegin));
    nbegin = nend + strlen(token);
  }
}

using namespace cocos2d;

bool GameObject::init()
{
  if (!cocos2d::CCSprite::init()) {
    return false;
  }

  this->screenSize_ = cocos2d::CCDirector::sharedDirector()->getWinSize();
  this->isActive_ = true;
  this->gameObjectType_ = kObjectTypeNone;

  return true;
}

void GameObject::changeState(CharacterStates newState)
{
  CCLOG("GameObject->changeState method should be overridden");
}

void GameObject::updateState(float deltaTime, const cocos2d::CCArray& listOfGameObjects)
{
  //CCLOG("updateStateWithDeltaTime method should be overridden");
}

cocos2d::CCRect GameObject::adjustedBoundingBox()
{
  CCLOG("GameObect adjustedBoundingBox should be overridden");
  return this->boundingBox();
}

cocos2d::CCAnimation * GameObject::loadPlistForAnimation(const char *animationName, const char *className)
{
  CCAnimation *animationToReturn;
  char plistFile[strlen(className)+10];
  sprintf(plistFile, "%s.plist", className);
  CCDictionary *plistDictionary = CCDictionary::createWithContentsOfFileThreadSafe(plistFile);
  CCDictionary *animationSettings = static_cast<CCDictionary *>(plistDictionary->objectForKey(animationName));

  float animationDelay = animationSettings->valueForKey("delay")->floatValue();
  animationToReturn = CCAnimation::create();
  animationToReturn->setDelayPerUnit(animationDelay);

  const char *animationFramePrefix = animationSettings->valueForKey("filenamePrefix")->getCString();
  const CCString *animationFrames = animationSettings->valueForKey("animationFrames");
  std::vector<std::string> animationFrameNumbers;
  str_split(animationFrames->m_sString, ",", animationFrameNumbers);

  for(std::vector<std::string>::iterator it = animationFrameNumbers.begin(); it != animationFrameNumbers.end(); ++it) {
    const char *frameNumber = it->c_str();
    char frameName[200];
    sprintf(frameName, "%s%s.png", animationFramePrefix, frameNumber);
    animationToReturn->addSpriteFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName));
  }

  return animationToReturn;
}
