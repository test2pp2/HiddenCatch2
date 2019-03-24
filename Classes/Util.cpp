#include "Util.h"

using namespace cocos2d;

Vec2 Util::GetCenterPosition() {
    const auto visible_size = Director::getInstance()->getVisibleSize();
    const Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 center = Vec2(visible_size.width / 2.0f + origin.x, visible_size.height / 2.0f + origin.y);
    return center;
}

GameInstance& GameInstance::Get() {
    static GameInstance instance;
    return instance;
}

GameInstance::GameInstance() = default;
