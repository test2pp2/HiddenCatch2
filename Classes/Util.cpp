#include "Util.h"
#include "network/HttpClient.h"
#include "ConstValue.h"

using namespace cocos2d;

Vec2 Util::GetCenterPosition() {
    const auto visible_size = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(visible_size.width / 2.0f + origin.x, visible_size.height / 2.0f + origin.y);
    return center;
}

Vec2 Util::GetLeftImagePosition() {
    const auto x = GetCenterPosition().x +
                   (ImageDesignSize::width / 2) +
                   (ImageDesignSize::height / 2);
    return Vec2(0, 0);
}

Vec2 Util::GetRightImagePosition() {
    return Vec2(0, 0);
}

void Util::StartDownloadImage(
    const std::string& url,
    const char* tag,
    const cocos2d::network::ccHttpRequestCallback& callback
) {
    network::HttpRequest* request = new (std::nothrow) network::HttpRequest();
    if (request == nullptr) {
        // LOG ERROR
        return;
    }
    request->setTag(tag);
    request->setUrl(url.c_str());
    request->setRequestType(network::HttpRequest::Type::GET);
    request->setResponseCallback(callback);
    network::HttpClient::getInstance()->send(request);
    request->release();
}

GameInstance& GameInstance::Get() {
    static GameInstance instance;
    return instance;
}

GameInstance::GameInstance() {
    user_info_ = std::make_shared<UserInfo>();
}

std::shared_ptr<UserInfo> GameInstance::user_info() const {
    return user_info_;
}


/*
UserInfo& GameInstance::user_info() {
    return user_info_;
}
*/

