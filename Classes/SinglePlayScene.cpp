#include "SinglePlayScene.h"
#include "ui/UIButton.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "Util.h"
#include "ConstValue.h"

using namespace cocos2d;

static Texture2D left_texture;
static Texture2D right_texture;

static Layer*   ui_layer = nullptr;
static Layer*   sprite_layer = nullptr;

bool CreateUiButton(Layer* layer) {
    assert(layer);

    const auto timer = Sprite::create("res/UI/Timer.png");
    timer->setPosition(
        {
            Util::GetCenterPosition().x,
            Util::GetCenterPosition().y - (ImageDesignSize::height / 2) + (BottomUiDesignSize::height / 2)
        }
    );
    layer->addChild(timer);

    const auto bottom_background = Sprite::create("res/UI/Bottom.png");
    bottom_background->setPosition(
        {
            Util::GetCenterPosition().x,
            Util::GetCenterPosition().y - (ImageDesignSize::height / 2) - (TimerDesignSize::height / 2)
        }
    );
    layer->addChild(bottom_background);

    // 타이머 아이콘
    const auto timer_item = Sprite::create("res/UI/TimerIcon.png");
    timer_item->setPosition(
        {
            bottom_background->getPosition().x + 300.0f,
            bottom_background->getPosition().y - 2.0f
        }
    );
    layer->addChild(timer_item);

    return true;
}

bool CreateSprite(Layer* layer) {
    assert(layer);

    auto left_image = Sprite::create("res/Common/TestLeftImage.png");
    left_image->setPosition(
        {
            Util::GetCenterPosition().x - (ImageDesignSize::width / 2) - (CenterSpaceDesignSize::width / 2),
            Util::GetCenterPosition().y + (BottomUiDesignSize::height / 2) + (TimerDesignSize::height / 2)
        }
    );
    layer->addChild(left_image);

    auto right_image = Sprite::create("res/Common/TestLeftImage.png");
    right_image->setPosition(
        {
            Util::GetCenterPosition().x + (ImageDesignSize::width / 2) + (CenterSpaceDesignSize::width / 2),
            Util::GetCenterPosition().y + (TimerDesignSize::height / 2) + (BottomUiDesignSize::height / 2)
        }
    );
    layer->addChild(right_image);

    return true;
}

Scene* SinglePlayScene::createScene() {
    return SinglePlayScene::create();
}

bool SinglePlayScene::init() {
    if (!Scene::init()) return false;

    ui_layer = Layer::create();
    //ui_layer->setPosition(Vec2::ZERO);
    this->addChild(ui_layer, ZOrder::kUI);
    CreateUiButton(ui_layer);

    sprite_layer = Layer::create();
    //ui_layer->setPosition(Vec2::ZERO);
    this->addChild(sprite_layer, ZOrder::kSprite);
    CreateSprite(ui_layer);


    //Util::StartDownloadImage("http://www.clker.com/cliparts/3/m/v/Y/E/V/small-red-apple-md.png", "left", CC_CALLBACK_2(SinglePlayScene::TestDownloadImage, this));
    //Util::StartDownloadImage(req_url, "right", CC_CALLBACK_2(SinglePlayScene::TestDownloadImage, this));
    
    return true;
}

void SinglePlayScene::TestDownloadImage(
    cocos2d::network::HttpClient* sender,
    cocos2d::network::HttpResponse* response
) {
    if (!response || !response->isSucceed()) {
        return;
    }

    const std::string tag = response->getHttpRequest()->getTag();

    std::vector<char>* buffer = response->getResponseData();

    auto image = std::make_shared<Image>();
    image->initWithImageData(reinterpret_cast<const unsigned char*>(&(buffer->front())), buffer->size());

    Sprite* sprite = nullptr;
    if (tag == "left") {
        left_texture.initWithImage(image.get());
        sprite = Sprite::createWithTexture(&left_texture);
        sprite->setPosition(Util::GetCenterPosition() + Vec2(200.0f, 0.0f));
    } else {
        right_texture.initWithImage(image.get());
        sprite = Sprite::createWithTexture(&right_texture);
        sprite->setPosition(Util::GetCenterPosition() - Vec2(200.0f, 0.0f));
    }
    this->addChild(sprite);
    
    //++download_image_count_;
    //OnCompleteDownloadallImage();
}
