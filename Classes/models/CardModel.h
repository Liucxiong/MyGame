#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "../configs/models/CardResConfig.h" //卡牌ui配置文件
#include "../views/CardView.h"
/// <summary>
/// 卡牌数据结构
/// </summary>
class CardModel {
private:
	card::CardSuitType suitType;	//卡片花色
	card::CardFaceType faceType;	//卡牌点数
	bool clickable = false;			//是否可点击
	int index = 0;					//卡牌在全局数组中的索引
	cocos2d::Vec2 position;			//中心位置
public:
	CardModel(card::CardSuitType suitType, card::CardFaceType faceType, bool isclick,int Index, cocos2d::Vec2 pos)
		: suitType(suitType), faceType(faceType), clickable(isclick), index(Index), position(pos) {
	}

	card::CardSuitType getSuitType() const { return suitType; }
	card::CardFaceType getFaceType() const { return faceType; }
	bool isClickable() const { return clickable; }
	void setClickable(bool val) { clickable = val; }
	void setPosition(const cocos2d::Vec2& pos) { position = pos; }
	cocos2d::Vec2 getPosition() const { return position; }
	int getIndex() const { return index; }
	void setIndex(int idx) { index = idx; }

	/// <summary>
	/// 返回卡牌的点数值
	/// </summary>
	/// <returns>Int</returns>
	int getCardFaceValue() const {
		return faceType;
	}
	/// <summary>
	/// 获取牌的花色值。
	/// </summary>
	/// <returns>牌的花色值，类型为 int。</returns>
	int getCardSuitValue() const {
		return suitType;
	}
};


#endif