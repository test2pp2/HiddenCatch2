#include "SinglePlayScene.h"
#include "ui/UIButton.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "Util.h"
#include "ConstValue.h"
#include "json11.hpp"

using namespace cocos2d;

static Texture2D left_texture;
static Texture2D right_texture;

static Layer* layers[LayerOrder::kSize] = { nullptr, };
static Sprite* timer_bar = nullptr;
static ProgressTimer* progress_timer_bar = nullptr;


void SinglePlayScene::RequestStageInfo(int32_t stage_id, const std::string& uid) {
    using namespace network;

    
    const std::string url = WebServerUrl + "/stage/req/" + std::to_string(stage_id) + "/" + uid;

    auto request = new HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([&](
        network::HttpClient* sender,
        network::HttpResponse* response
        ) {
            if (!response) {
                return;
            }
            const auto response_code = response->getResponseCode();
            if (!response->isSucceed()) {
                return;
            }
            if (response_code != 200) {
                return;
            }

            std::string error;
            std::vector<char>* buffer = response->getResponseData();
            char* concatenated = new char[buffer->size() + 1];
            std::string payload(buffer->begin(), buffer->end());
            strcpy(concatenated, payload.c_str());
            json11::Json json_object = json11::Json::parse(concatenated, error);
            delete[] concatenated;
           
            // json 오브젝트 파싱해주기
            /*
            hidden_points_.clear();
            left_hidden_rects_.clear();
            right_hidden_rects_.clear();

            for (auto& hidden_point : json_object["hidden_points"].array_items()) {
                HiddenPoint tmp;
                tmp.x = static_cast<float>(hidden_point["x"].int_value());
                tmp.y = static_cast<float>(hidden_point["y"].int_value());
                tmp.width = hidden_point["width"].int_value();
                tmp.height = hidden_point["height"].int_value();
                hidden_points_.emplace_back(tmp);
            }

            auto current_stage_count = json_object["current_stage_count"].int_value();
            auto total_stage_count = json_object["total_stage_count"].int_value();

            total_hidden_point_count_ = hidden_points_.size();
            CreateLabel(current_stage_count + 1, total_stage_count);

            auto left_image_url = json_object["left_image_url"].string_value();
            auto right_image_url = json_object["right_image_url"].string_value();
            StartDownloadLeftImage(left_image_url.c_str());
            StartDownloadRightImage(right_image_url.c_str());

            for (auto hidden_point : hidden_points_) {
                auto x = hidden_point.x - (hidden_point.width * 0.5f);
                auto y = (hidden_point.y + kTimerOutlinerHeight + kBottomSpriteHeight) - (hidden_point.height * 0.5f);
                Rect left_rect(x, y, hidden_point.width, hidden_point.height);
                left_hidden_rects_.push_back(left_rect);

                Rect right_rect(x + kMiddleSpace + kImageWidth, y, hidden_point.width, hidden_point.height);
                right_hidden_rects_.push_back(right_rect);
            }
            */
    });

    HttpClient::getInstance()->send(request);
    request->release();
}

/****************************************************************************
 *
 * ui 관련 버튼 생성
 * 
 **/
bool CreateUiButton(Scene* scene, Layer* layer) {
    assert(layer);

    // 타이머 생성
    timer_bar = Sprite::create("res/UI/TimerBar.png");

    // 타이머 아웃라이너
    auto timer_outline_sprite = Sprite::create("res/UI/TimerOutliner.png");
    const Size size = timer_outline_sprite->getContentSize();
    timer_outline_sprite->setPosition(
        Util::GetCenterPosition().x,
        Util::GetCenterPosition().y - (ImageDesignSize::height / 2) + (BottomUiDesignSize::height / 2)
    );
    timer_outline_sprite->setVisible(true);
    layer->addChild(timer_outline_sprite);

    progress_timer_bar = ProgressTimer::create(timer_bar);
    progress_timer_bar->setPosition(timer_outline_sprite->getPosition());
    progress_timer_bar->setMidpoint(Vec2(-1.0f, 0.0f));
    progress_timer_bar->setBarChangeRate(Vec2(1, 0));
    progress_timer_bar->setType(ProgressTimer::Type::BAR);
    progress_timer_bar->setPercentage(100);
    layer->addChild(progress_timer_bar);
    
    layer->schedule([](float /*dt*/) {
        //CCLOG("timer updated");
        const float kTimerMaxSec = 45;
        const float percentage = progress_timer_bar->getPercentage();
        progress_timer_bar->setPercentage(percentage - (100 / (kTimerMaxSec * 10)));
        const float current_percentage = progress_timer_bar->getPercentage();
        if (current_percentage <= 0.0f) {
            CCLOG("Game over: %f", percentage);
        } else if (current_percentage < 20.0f) {
            timer_bar->setColor(Color3B(255, 0, 0));
        } else if (current_percentage < 50.0f) {
            timer_bar->setColor(Color3B(255, 211, 0));
        }
    }, 1.0f / 10.0f, "timer");

    // ui 백그라운드
    const auto bottom_background = Sprite::create("res/UI/Bottom.png");
    bottom_background->setPosition(
        Util::GetCenterPosition().x,
        Util::GetCenterPosition().y - (ImageDesignSize::height / 2) - (TimerDesignSize::height / 2)
    );
    layer->addChild(bottom_background);

    // 타이머 아이콘
    const auto timer_item = Sprite::create("res/UI/TimerIcon.png");
    timer_item->setPosition(
        bottom_background->getPosition().x + 300.0f,
        bottom_background->getPosition().y - 2.0f
    );
    layer->addChild(timer_item);

    return true;
}

/****************************************************************************
 *
 * 스프라이트 생성
 *
 **/
bool CreateSprite(Scene* scene, Layer* layer) {
    assert(layer);
    return true;
}

/****************************************************************************
 *
 * 스프라이트 생성
 *
 **/
Scene* SinglePlayScene::createScene() {
    return SinglePlayScene::create();
}

/****************************************************************************
 *
 * 소멸자
 *
 **/
SinglePlayScene::~SinglePlayScene() {
    CCLOG("SinnglePlayScene dtor called");
}

/****************************************************************************
 *
 * 씬 초기화
 *
 **/
bool SinglePlayScene::init() {
    if (!Scene::init()) return false;

    layers[LayerOrder::kUi] = Layer::create();
    layers[LayerOrder::kSprite] = Layer::create();

    this->addChild(layers[LayerOrder::kUi], LayerOrder::kUi);
    CreateUiButton(this, layers[LayerOrder::kUi]);

    this->addChild(layers[LayerOrder::kSprite], LayerOrder::kSprite);
    CreateSprite(this, layers[LayerOrder::kSprite]);

    RequestStageInfo(1, "abcd");

    // 왼쪽 이미지 다운로드
    Util::StartDownloadImage(
        "https://s3.ap-northeast-2.amazonaws.com/s3hiddencatch/icon_1.png", 
        "left",
        CC_CALLBACK_2(SinglePlayScene::StartDownloadImage, this)
    );

    // 오른쪽 이미지 다운로드
    Util::StartDownloadImage(
        "https://s3.ap-northeast-2.amazonaws.com/s3hiddencatch/icon_1.png",
        "right",
        CC_CALLBACK_2(SinglePlayScene::StartDownloadImage, this)
    );
    
    return true;
}

/****************************************************************************
 *
 * 게임 시작
 *
 **/
void SinglePlayScene::StartGame(float max_game_time) {

}

/****************************************************************************
 *
 * 이미지 2개 다운로드 완료 후 처리
 *
 **/
void SinglePlayScene::OnCompleteDownloadImages() {
    // 이미지 다운로드 끝나고 게임 시작 알림
    StartGame(10.0f);
}

/****************************************************************************
 *
 * 이미지 다운로드
 *
 **/
void SinglePlayScene::StartDownloadImage(
    cocos2d::network::HttpClient* sender,
    cocos2d::network::HttpResponse* response
) {
    if (!response || !response->isSucceed()) {
        // 네트워크 상태가 좋지 않아서 팝업 띄우고 retry

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
        sprite->setPosition(
           Util::GetCenterPosition().x - (ImageDesignSize::width / 2) - (CenterSpaceDesignSize::width / 2),
           Util::GetCenterPosition().y + (BottomUiDesignSize::height / 2) + (TimerDesignSize::height / 2)
        );
    } else {
        right_texture.initWithImage(image.get());
        sprite = Sprite::createWithTexture(&right_texture);
        sprite->setPosition(
                Util::GetCenterPosition().x + (ImageDesignSize::width / 2) + (CenterSpaceDesignSize::width / 2),
                Util::GetCenterPosition().y + (TimerDesignSize::height / 2) + (BottomUiDesignSize::height / 2)
        );
    }

    layers[LayerOrder::kSprite]->addChild(sprite);
    
    ++image_download_count_;
    if (image_download_count_ >= 2) {
        OnCompleteDownloadImages();
    }
}
