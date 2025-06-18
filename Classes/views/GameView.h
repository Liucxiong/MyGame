#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "../models/CardModel.h"
#include "../controllers/CardController.h"

/// <summary>
/// GameView 类表示游戏场景，负责管理和显示卡牌视图，并处理相关的用户交互。
/// </summary>
class GameView : public cocos2d::Scene {
private:
	CardController* _controller; // 控制器，用于共享处理牌的逻辑
public:
	static GameView* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	//动态添加一张牌到游戏视图中
	void addCard(CardView* view, const cocos2d::Vec2& pos,int type);
	CREATE_FUNC(GameView);
};

#endif