#pragma once

#include "cocos2d.h"

namespace cocos2d {
namespace network {
class HttpResponse;
class HttpClient;
}
}

class SinglePlayScene final : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual ~SinglePlayScene();

    bool init() override;

    
    //cocos2d::Texture2D left_texture_;
    //cocos2d::Texture2D right_texture_;
private:
    void RequestStageInfo(int32_t stage_id, const std::string& uid);
    void StartDownloadImage(cocos2d::network::HttpClient* sender, cocos2d::network::HttpResponse* response);

    void StartGame(float max_game_time);
    void OnCompleteDownloadImages();
    CREATE_FUNC(SinglePlayScene);

    int32_t image_download_count_ = 0;
};
