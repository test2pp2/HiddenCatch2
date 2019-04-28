#include "LobbyScene.h"
#include "ui/UIButton.h"
#include "ConstValue.h"
#include "Util.h"
#include "SinglePlayScene.h"

using namespace cocos2d;

static Layer* layers[LayerOrder::kSize] = {nullptr, };
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

// 공통으로 옮겨야 함
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

    layers[LayerOrder::kUi] = Layer::create();
    this->addChild(layers[LayerOrder::kUi], LayerOrder::kUi);
    CreateUiButton(layers[LayerOrder::kUi]);

    layers[LayerOrder::kSprite] = Layer::create();
    this->addChild(layers[LayerOrder::kSprite], LayerOrder::kSprite);

    if (!RequestUserInfo("http://aaaa")) {
        // LOG_ERROR 핸들링

    }

    return true;
}
