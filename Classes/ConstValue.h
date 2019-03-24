#pragma once
#include <cstdint>
#include "SimpleAudioEngine.h"

static auto AudioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

enum ZOrder { kSprite = 0, kUI };

//static cocos2d::ScaleTo* SCALE_UP_BUTTON         = cocos2d::ScaleTo::create(0.2f, 1.2f);
//static cocos2d::ScaleTo* SCALE_NORMAL_BUTTON     = cocos2d::ScaleTo::create(0.2f, 1.0f);

static float kScaleUpDuration     = 0.2f;
static float kScaleNormalDuration = 0.2f;

#define SCALE_UP_BUTTON     cocos2d::ScaleTo::create(kScaleUpDuration, 1.2f)
#define SCALE_NORMAL_BUTTON cocos2d::ScaleTo::create(kScaleNormalDuration, 1.0f)