#include "GameView.h"
#include "SimpleAudioEngine.h"

#include "CardView.h"

#include "../configs/loaders/LevelConfigLoader.h"

USING_NS_CC;

GameView* GameView::createScene() {
	return GameView::create();
}

bool GameView::init()
{
    if (!Scene::init()) return false;
	_controller = new CardController();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 1. 整体灰色背景（相当于外层边框）
    auto greyBG = LayerColor::create(Color4B(100, 100, 100, 255),
        visibleSize.width,
        visibleSize.height);
    greyBG->setPosition(origin);
    this->addChild(greyBG, 0);

    // 2. 上半部分棕色区块
    float brownHeight = visibleSize.height * 0.7211f; // 你可以调整比例
    auto brownBG = LayerColor::create(Color4B(185, 140, 75, 255),
        visibleSize.width,
        brownHeight);
    brownBG->setPosition(origin.x,
        origin.y + visibleSize.height - brownHeight);
    this->addChild(brownBG, 1);

    // 3. 底部紫色区块
    float purpleHeight = visibleSize.height - brownHeight;
    auto purpleBG = LayerColor::create(Color4B(128, 0, 128, 255),
        visibleSize.width,
        purpleHeight);
    purpleBG->setPosition(origin);
    this->addChild(purpleBG, 1);


    //4. 创建一个 Label
    auto undoLabel = Label::createWithTTF(u8"回退", "fonts/simhei.ttf", 28);
    undoLabel->setPosition(Vec2(visibleSize.width * 0.8f, visibleSize.height * 0.12f));
    this->addChild(undoLabel, 10);

    //添加触摸监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [undoLabel, this](Touch* t, Event* e) {
        Vec2 loc = undoLabel->convertToNodeSpace(t->getLocation());
        Rect bb(0, 0, undoLabel->getContentSize().width,
            undoLabel->getContentSize().height);
        if (bb.containsPoint(loc)) {
            // 瞬时改变颜色作为按下反馈
            undoLabel->setColor(Color3B::YELLOW);
            return true;
        }
        return false;
        };
    listener->onTouchEnded = [undoLabel, this](Touch* t, Event* e) {
		undoLabel->setColor(Color3B::WHITE);  // 恢复原色
        _controller->undoLastMove();
        };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, undoLabel);


    return true;
}

//在什么位置摆放什么卡牌,输入view和摆放位置中心，将自动计算左下角位置，注意需要的回调函数类型
void GameView::addCard(CardView*  view, const cocos2d::Vec2 & pos,int type)
{
    if (!view) {
        CCLOG("Failed to create card!");
        return;
    }
	auto cardsize = view->getContentSize();
    view->setPosition(cocos2d::Vec2(pos.x - cardsize.width / 2,pos.y - cardsize.width / 2));

    if (type == 0) {    //手牌区点击事件
        view->setClickCallback([this](CardView* sender) {
            this->_controller->onHandCardClicked(sender);
            });
    }
	else {              //桌牌区点击事件
        view->setClickCallback([this](CardView* sender) {
            this->_controller->onTableCardClicked(sender);
            });
    }
    this->addChild(view, view->getLocalZOrder());

    CCLOG("Card added at (%.1f, %.1f)", pos.x,pos.y);
}
