#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__  

#include "cocos2d.h"  
#include "../configs/models/CardResConfig.h"

/// <summary>
/// 卡牌UI视图类，通过多个精灵组合而成
/// </summary>
class CardView : public cocos2d::Node  
{  
public:  
    static CardView* createCard(card::CardFaceType number,  
        card::CardSuitType suit);

    bool initCard(card::CardFaceType number,  
        card::CardSuitType suit);  

    void setClickable(bool clickable) { _clickable = clickable; }
    bool isClickable() const { return _clickable; }

    //点击卡牌回调函数
    using ClickCallback = std::function<void(CardView*)>;
    void setClickCallback(const ClickCallback& cb) { _clickCb = cb; }

    //卡牌抖动效果
	void cardShake();  

private:  
    cocos2d::Sprite* background;  // 卡牌底图  
    cocos2d::Sprite* bigNumSprite;   // 点数大图片，如 "3", "A", "K"  
    cocos2d::Sprite* smallNumSprite;   // 点数小图片，如 "3", "A", "K"  
    cocos2d::Sprite* suitSprite;  // 花色图片，如 "♠", "♦"  
    bool _clickable = false;    //是否可被点击
	//卡牌UI具体摆放布局函数
    bool layoutCard();    

    ClickCallback _clickCb;//存储外部注册的回调
};  

#endif