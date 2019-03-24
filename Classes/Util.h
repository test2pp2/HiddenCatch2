#pragma once

#include "cocos2d.h"

class Util {
public:
    static cocos2d::Vec2 GetCenterPosition();
};

class GameInstance {
public:
    static GameInstance& Get();
    GameInstance(const GameInstance& instance) = delete;
    GameInstance(const GameInstance&& instance) = delete;
    GameInstance& operator=(const GameInstance& instance) = delete;
    GameInstance& operator=(GameInstance&& instance) = delete;


private:
    GameInstance();
};



