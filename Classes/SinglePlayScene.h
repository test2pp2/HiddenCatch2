#pragma once

#include "cocos2d.h"

class SinglePlayScene final : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual ~SinglePlayScene() = default;

    bool init() override;

    CREATE_FUNC(SinglePlayScene);
private:

};
