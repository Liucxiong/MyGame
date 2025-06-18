#include "CardView.h"

USING_NS_CC;

CardView* CardView::createCard(card::CardFaceType number,
        card::CardSuitType suit)
{
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->initCard(number, suit)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::initCard(card::CardFaceType number,
    card::CardSuitType suit)
{
    if (!Node::init()) return false;

	bool isRed = (suit == card::CardSuitType::CST_DIAMONDS || suit == card::CardSuitType::CST_HEARTS);
    // 1. 添加背景图
    std::string aheadPath = "res/number/";
    std::string colorType = isRed ? "red_" : "black_";
    background = Sprite::create("res/card_general.png");
	//设置锚点为左下角
    background->setAnchorPoint(Vec2::ZERO);
    background->setPosition(Vec2::ZERO);
    this->addChild(background);

    //2. 创建大数字图片
    std::string bigNumImage = aheadPath + "big_" + colorType + card::convertCardFace.at(number) + ".png";
    bigNumSprite = Sprite::create(bigNumImage);
    background->addChild(bigNumSprite);
       
    //3. 创建小数字图片
    std::string smallNumImage = aheadPath + "small_" + colorType + card::convertCardFace.at(number) + ".png";
    smallNumSprite = Sprite::create(smallNumImage);
    background->addChild(smallNumSprite);

    // 4. 创建花色图标
    std::string suitImage = "res/suits/" + card::convertCardSuit.at(suit) + ".png";
    suitSprite = Sprite::create(suitImage);
    background->addChild(suitSprite);

    // 5. 把 CardView 自身撑成和背景一样大
    this->setContentSize(background->getContentSize());

    //  添加触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    // 吞掉触摸事件，保证 onTouchEnded 能触发
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [this](Touch* touch, Event* event) {
        // 把触摸点转到背景的局部坐标系
        Vec2 loc = background->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0,
                         background->getContentSize().width,
                         background->getContentSize().height);
        // 如果点在背景范围内，就“消费”这个事件
        return rect.containsPoint(loc);
    };
    listener->onTouchEnded = [this](Touch* touch, Event* event) {
        if (!_clickable) {
            CCLOG("CardView is not clickable.");
            return;
        }
        if (_clickCb) {
            _clickCb(this);
        }
        else {
            CCLOG("CardView clicked: %p", this);
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return layoutCard();
}

bool CardView::layoutCard()
{
    // 确保背景、精灵都已创建
    if (!background || !bigNumSprite || !smallNumSprite || !suitSprite)
        return false;

    auto sz = background->getContentSize();
    float w = sz.width, h = sz.height;

    // 背景已在 (0,0)
    // 在 background 的本地坐标系里摆放：
    // 大数字：正中间
    bigNumSprite->setPosition(Vec2(w * 0.5f, h * 0.4f));
    // 小数字：左上角
    smallNumSprite->setPosition(Vec2(w * 0.2f, h * 0.8f));
    // 花色图标：右上角
    suitSprite->setPosition(Vec2(w * 0.8f, h * 0.8f));
    return true;
}

void CardView::cardShake() {
    auto moveLeft = MoveBy::create(0.05f, Vec2(-10, 0));
    auto moveRight = MoveBy::create(0.1f, Vec2(20, 0));
    auto moveBack = MoveBy::create(0.05f, Vec2(-10, 0));
    auto shake = Sequence::create(moveLeft, moveRight, moveBack, nullptr);
    this->runAction(Repeat::create(shake, 2));
}