#pragma once
#include <cstdint>
#include <string>
#include "SimpleAudioEngine.h"

#define AUDIO_ENGINE CocosDenshion::SimpleAudioEngine::getInstance()
#define SCALE_UP_BUTTON     cocos2d::ScaleTo::create(kScaleUpDuration, 1.2f)
#define SCALE_NORMAL_BUTTON cocos2d::ScaleTo::create(kScaleNormalDuration, 1.0f)

enum ZOrder { kSprite = 0, kUI };
enum ImagePlace { kNone = 0, kLeft, kRight };

//static cocos2d::ScaleTo* SCALE_UP_BUTTON         = cocos2d::ScaleTo::create(0.2f, 1.2f);
//static cocos2d::ScaleTo* SCALE_NORMAL_BUTTON     = cocos2d::ScaleTo::create(0.2f, 1.0f);

static float kScaleUpDuration = 0.2f;
static float kScaleNormalDuration = 0.2f;

struct ImageDesignSize {
    static const int32_t width = 956;
    static const int32_t height = 900;
};

struct TimerDesignSize {
    static const uint32_t width = 1920;
    static const uint32_t height = 16;
};

struct BottomUiDesignSize {
    static const uint32_t width = 1920;
    static const uint32_t height = 164;
};

struct CenterSpaceDesignSize {
    static const uint32_t width = 8;
    static const uint32_t height = 1080;
};
