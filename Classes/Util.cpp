#include "Util.h"
#include "network/HttpClient.h"

using namespace cocos2d;

Vec2 Util::GetCenterPosition() {
    const auto visible_size = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(visible_size.width / 2.0f + origin.x, visible_size.height / 2.0f + origin.y);
    return center;
}

void Util::StartDownloadImage(
    const std::string& url,
    const cocos2d::network::ccHttpRequestCallback& callback
) {
    network::HttpRequest* request = new (std::nothrow) network::HttpRequest();
    if (request == nullptr) {
        // LOG ERROR
        return;
    }
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

GameInstance::GameInstance() = default;
