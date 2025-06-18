#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include <map>
#include "../configs/loaders/LevelConfigLoader.h"	//加载静态数据
#include "../models/CardModel.h"

#include "../views/CardView.h"

/// <summary>
/// 现存数据服务类
/// </summary>
class DataService {
private:
	std::map<CardView*, CardModel*> cardView2Model;	//全局卡牌视图和模型的映射关系
	std::vector<CardView*> cardViewsInTable;	//桌面卡牌视图列表
	std::vector<CardView*> cardViewsInHand;		//手牌卡牌视图列表
public:
    static DataService& get();  // 全局访问入口返回单实例对象

	void InitData();					//初始化数据

	void addCardToHand(CardView* view);			//新增手牌
	void addCardToTable(CardView* view);		//新增桌面卡牌
	//清空所有卡牌
	void clear();
	//获取卡牌模型								
	CardModel* getCardModel(CardView* view);
	//获取桌面卡牌数量	
	int getCardCountInTable() const;
	//通过下标获取桌面卡牌视图				
	CardView* getCardViewInTable(int idx);
	//获取桌面数组最后一张卡牌视图		
	CardView* getCardLastViewInTable();
	//通过下标设置桌面卡牌视图		
	bool setCardViewInTable(int idx, CardView* view);	

	//获取手牌卡牌数量
	int getCardCountInHand() const;
	//通过下标获取手牌卡牌视图				
	CardView* getCardViewInHand(int idx);
	//获取手牌最后一张卡牌视图		
	CardView* getCardLastViewInHand();
	//通过下标设置手牌卡牌视图		
	bool setCardViewInHand(int idx, CardView* view);

	//交换桌面卡牌视图位置	
	bool swapCardViewsInTable(int idx1, int idx2);
	//交换手牌卡牌视图位置	
	bool swapCardViewsInHand(int idx1, int idx2);	
};

#endif