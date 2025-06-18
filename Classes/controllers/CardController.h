#ifndef __CARD_CONTROLLER_H__
#define __CARD_CONTROLLER_H__

#include "../views/CardView.h"
#include "../services/GameModelFromLevelGenerator.h"
#include "../services/UndoService.h"
#include "../models/CardModel.h"

class CardController
{
private:
	bool isChangingCard = false; // 是否正在交换卡牌,简单互斥防止抖动
public:
	//卡牌点击处理事件
	// 手牌区
	void onHandCardClicked(CardView* cardView);
	//桌牌区
	void onTableCardClicked(CardView* cardView);
	/// <summary>
	/// 交换手牌区一张牌到顶部区域，并执行相应的动画，卡牌点击回调函数之一
	/// </summary>
	/// <param name="index">要交换到顶层的下标</param>
	void switchCardInHandToTop(int index);
	/// <summary>
	/// 将桌面上的指定卡牌移动到手牌顶部。卡牌点击回调函数之二
	/// </summary>
	/// <param name="index">要移动的卡牌在桌面上的索引。</param>
	void switchCardInTableToHandTop(int index);
	/// <summary>
	/// 桌牌和手牌匹配逻辑
	/// </summary>
	/// <param name="tableIndex">桌牌下标</param>
	/// <returns>true / false</returns>
	bool isAbleToMatch(int tableIndex) const;
	/// <summary>
	/// 撤销将手牌中两张牌交换到顶部的操作。
	/// </summary>
	/// <param name="idxA">要交换的第一张手牌的索引。</param>
	/// <param name="idxB">要交换的第二张手牌的索引。</param>
	void undoSwitchCardInHandToTop(int idxA,int idxB);
	/// <summary>
	/// 将手牌中的牌回退到桌面
	/// </summary>
	/// <param name="idxA">桌面牌数组的索引</param>
	/// <param name="idxB">手牌区卡片数组索引</param>
	void undoSwitchCardInTableToHandTop(int idxA, int idxB);
	/// <summary>
	/// 撤销上一次操作。作为lable的回调函数使用。
	/// </summary>
	void undoLastMove();

};

#endif