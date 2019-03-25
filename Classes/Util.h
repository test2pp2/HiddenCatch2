#pragma once

#include "cocos2d.h"
#include "network/HttpRequest.h"

class Util {
public:
    static cocos2d::Vec2 GetCenterPosition();
    static void StartDownloadImage(
        const std::string& url,
        const cocos2d::network::ccHttpRequestCallback& callback
    );
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
