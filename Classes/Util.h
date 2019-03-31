#pragma once

#include "cocos2d.h"
#include "network/HttpRequest.h"

class Util {
public:
    static cocos2d::Vec2 GetCenterPosition();
    static cocos2d::Vec2 GetLeftImagePosition();
    static cocos2d::Vec2 GetRightImagePosition();
    static void StartDownloadImage(
        const std::string& url,
        const char* tag,
        const cocos2d::network::ccHttpRequestCallback& callback
    );
};

struct UserInfo {
    size_t user_id;
    std::string user_nickname;
    int32_t find_hint_count;
    int32_t stop_timer_count;
    int32_t complete_stage;
};

struct StageInfo {
    size_t max_stage_count;
};

class GameInstance {
public:
    static GameInstance& Get();
    GameInstance(const GameInstance& instance) = delete;
    GameInstance(const GameInstance&& instance) = delete;
    GameInstance& operator=(const GameInstance& instance) = delete;
    GameInstance& operator=(GameInstance&& instance) = delete;


    std::shared_ptr<UserInfo> user_info() const;
    //StageInfo& stage_info();
    
private:
    GameInstance();
    std::shared_ptr<UserInfo> user_info_;
    //StageInfo stage_info_;
};
