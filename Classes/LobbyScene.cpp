#include "LobbyScene.h"
#include "ui/UIButton.h"
#include "ConstValue.h"
#include "Util.h"

using namespace cocos2d;

static Node*       ui_node_repository = nullptr;
static ui::Button* play_single_mode_button = nullptr;

static bool CreateHudButton(Scene* scene) {
    ui_node_repository = Node::create();
    ui_node_repository->setPosition(Vec2::ZERO);
    scene->addChild(ui_node_repository, ZOrder::kUI);

    play_single_mode_button = ui::Button::create(
        "res/UI/PlaySingleModeButton.png", 
        "res/UI/PlaySingleModeButton.png", 
        "res/UI/PlaySingleModeButton.png"
    );

    if (play_single_mode_button == nullptr) return false;

    
    play_single_mode_button->setPosition(Util::GetCenterPosition());

    play_single_mode_button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) mutable {
        if (type == ui::Widget::TouchEventType::BEGAN) {
            auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
            //AudioEngine->playEffect("sounds/ButtonClick.mp3");
            
            play_single_mode_button->runAction(SCALE_UP_BUTTON);
        } else if (type == ui::Widget::TouchEventType::ENDED) {
            play_single_mode_button->runAction(SCALE_NORMAL_BUTTON);
        } else if (type == ui::Widget::TouchEventType::CANCELED) {
            play_single_mode_button->runAction(SCALE_NORMAL_BUTTON);
        }
    });

    ui_node_repository->addChild(play_single_mode_button);

    return true;
}

Scene* LobbyScene::createScene() {
    return LobbyScene::create();
}

bool LobbyScene::init() {
    if (!Scene::init()) return false;

    CreateHudButton(this);

    return true;
}
