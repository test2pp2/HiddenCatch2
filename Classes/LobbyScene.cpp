#include "LobbyScene.h"
#include "ui/UIButton.h"
#include "ConstValue.h"
#include "Util.h"
#include "SinglePlayScene.h"

using namespace cocos2d;

static Layer*   ui_layer = nullptr;
static Layer*   sprite_layer = nullptr;
static ui::Button* play_single_button = nullptr;

static bool CreateUiButton(Layer* layer) {
    assert(layer);
    play_single_button = ui::Button::create(
        "res/UI/PlaySingleModeButton.png", 
        "res/UI/PlaySingleModeButton.png", 
        "res/UI/PlaySingleModeButton.png"
    );

    if (play_single_button == nullptr) return false;

    play_single_button->setPosition(Util::GetCenterPosition() + Vec2(300.0f, -300.0f));
    play_single_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) mutable {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            AUDIO_ENGINE->playEffect("sounds/ButtonClick.mp3");
            
            play_single_button->runAction(SCALE_UP_BUTTON);
        } else if (type == ui::Widget::TouchEventType::ENDED) {
            play_single_button->runAction(SCALE_NORMAL_BUTTON);
            Director::getInstance()->replaceScene(SinglePlayScene::createScene());
        } else if (type == ui::Widget::TouchEventType::CANCELED) {
            play_single_button->runAction(SCALE_NORMAL_BUTTON);
        }
    });

    layer->addChild(play_single_button);
    return true;
}

static bool CreateSprite(Layer* layer) {
    assert(layer);

    auto left_image = Sprite::create();
    left_image->setPosition(Vec2::ZERO);
    layer->addChild(left_image);
   

    return true;
}

static bool RequestUserInfo(const std::string& url) {
    GameInstance::Get().user_info()->user_id = 100;
    GameInstance::Get().user_info()->user_nickname = "abcd";
    GameInstance::Get().user_info()->find_hint_count = 0;
    GameInstance::Get().user_info()->stop_timer_count = 0;
    GameInstance::Get().user_info()->complete_stage = 0;
    return true;
}

Scene* LobbyScene::createScene() {
    return LobbyScene::create();
}

bool LobbyScene::init() {
    if (!Scene::init()) return false;

    ui_layer = Layer::create();
    this->addChild(ui_layer, ZOrder::kUI);
    CreateUiButton(ui_layer);

    sprite_layer = Layer::create();
    this->addChild(sprite_layer, ZOrder::kSprite);

    if (!RequestUserInfo("http://aaaa")) {
        // LOG_ERROR �ڵ鸵

    }

    return true;
}
