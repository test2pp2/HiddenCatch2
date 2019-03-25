#include "SinglePlayScene.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "Util.h"

using namespace cocos2d;

bool SinglePlayScene::init() {
    if (!Scene::init()) return false;

    Util::StartDownloadImage("http://aa", CC_CALLBACK_2(SinglePlayScene::TestDownloadImage, this));
    
    return true;
}

void SinglePlayScene::TestDownloadImage(
    cocos2d::network::HttpClient* sender,
    cocos2d::network::HttpResponse* response
) {
    if (!response || !response->isSucceed()) {
        return;
    }

    std::vector<char>* buffer = response->getResponseData();

    Image* image = new Image();
    image->initWithImageData(reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());
    
    Texture2D right_image;
    right_image.initWithImage(image);
    auto right_image_sprite = Sprite::createWithTexture(&right_image);
    right_image_sprite->setPosition(Util::GetCenterPosition());
    this->addChild(right_image_sprite);
    delete image;
    //++download_image_count_;
    //OnCompleteDownloadallImage();
}
