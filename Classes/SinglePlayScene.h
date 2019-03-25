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

    virtual ~SinglePlayScene() = default;

    bool init() override;
    
    void TestDownloadImage(
        cocos2d::network::HttpClient* sender,
        cocos2d::network::HttpResponse* response
    );

    CREATE_FUNC(SinglePlayScene);
private:

};
