#include "GameModelFromLevelGenerator.h"

DataService& DataService::get() {
	static DataService instance;
	return instance;
}

void DataService::InitData() {
	std::vector<CardModel*> tableModel = loadCardsFromJson("levelConfig.json", "Playfield");
	std::vector<CardModel*> handModel = loadCardsFromJson("levelConfig.json", "Stack");
	cardViewsInTable.resize(0);
	cardViewsInTable.resize(0);
	//创建桌牌初始数据
	for (const auto& i : tableModel) {
		auto view = CardView::createCard(i->getFaceType(), i->getSuitType());
		view->setClickable(true);
		view->setLocalZOrder(i->getIndex() + 2); // 设置本地 Z 顺序
		cardView2Model[view] = i;
		cardViewsInTable.emplace_back(view);
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//创建手牌初始数据,位置属性自动排列
	for (auto& i : handModel) {
		auto view = CardView::createCard(i->getFaceType(), i->getSuitType());
		i->setPosition(cocos2d::Vec2(visibleSize.width * 0.14 + 0.8 * view->getContentSize().width * i->getIndex(),
			visibleSize.height * 0.1f)); // 设置手牌堆叠区卡片中心
		view->setClickable(true);
		view->setLocalZOrder(i->getIndex() + 2); // 设置本地 Z 顺序
		cardView2Model[view] = i;
		cardViewsInHand.emplace_back(view);
	}
	//手牌区最后一张属性有别于其他卡牌独立设置
	CardView* endView = cardViewsInHand.back();
	CardModel* endModel = cardView2Model[endView];
	endModel->setClickable(false); endView->setClickable(false);
	endModel->setPosition(cocos2d::Vec2(visibleSize.width * 0.6,
		visibleSize.height * 0.1f)); // 设置手牌堆叠区卡片中心
}

void DataService::addCardToHand(CardView* view) {
	cardViewsInHand.emplace_back(view);
}

void DataService::addCardToTable(CardView* view) {
	cardViewsInTable.emplace_back(view);
}

void DataService::clear() {
	// 释放 CardView（如果它没有被 Cocos 的场景树托管）
	for (auto view : cardViewsInHand) {
		if (view->getParent()) {
			view->removeFromParent(); // 只移除，不删除
		}
		else {
			delete view; // 如果是自己 new 出来的、未交给 Cocos 托管
		}
	}

	for (auto view : cardViewsInTable) {
		if (view->getParent()) {
			view->removeFromParent();
		}
		else {
			delete view;
		}
	}

	// 删除 CardModel（你手动 new 的，一定要释放）
	for (auto& pair : cardView2Model) {
		delete pair.second;
	}

	// 清空容器
	cardViewsInHand.clear();
	cardViewsInTable.clear();
	cardView2Model.clear();
}

CardModel* DataService::getCardModel(CardView* view) {
	return cardView2Model[view];
}
// 获取桌牌区的卡牌数量
int DataService::getCardCountInTable() const {
	return cardViewsInTable.size();
}

CardView* DataService::getCardViewInTable(int idx) {
	if (idx < 0 || idx >= cardViewsInTable.size()) {
		return nullptr; // 索引越界
	}
	return cardViewsInTable[idx];
}

CardView* DataService::getCardLastViewInTable() {
	if(cardViewsInTable.empty()) {
		return nullptr; // 如果桌牌区没有卡牌
	}
	return cardViewsInTable.back(); // 如果没有找到对应的 CardView
}

bool DataService::setCardViewInTable(int idx, CardView* view) {
	if (idx < 0 || idx >= cardViewsInTable.size()) {
		return false; // 索引越界
	}
	cardViewsInTable[idx] = view;
	return true;
}

// 获取手牌区的卡牌数量
int DataService::getCardCountInHand() const {
	return cardViewsInHand.size();
}

CardView* DataService::getCardViewInHand(int idx) {
	if (idx < 0 || idx >= cardViewsInHand.size()) {
		return nullptr; // 索引越界
	}
	return cardViewsInHand[idx];
}

CardView* DataService::getCardLastViewInHand() {
	if(cardViewsInHand.empty()) {
		return nullptr; // 如果手牌区没有卡牌
	}
	return cardViewsInHand.back(); // 返回手牌区最后一张卡牌的视图
}

bool DataService::setCardViewInHand(int idx, CardView* view) {
	if (idx < 0 || idx >= cardViewsInHand.size()) {
		return false; // 索引越界
	}
	cardViewsInHand[idx] = view;
	return true;
}

bool DataService::swapCardViewsInTable(int idx1, int idx2) {
	if(idx1 < 0 || idx1 >= cardViewsInTable.size() || idx2 < 0 || idx2 >= cardViewsInTable.size()) {
		return false; // 索引越界
	}
	std::swap(cardViewsInTable[idx1], cardViewsInTable[idx2]);
	return true;
}

bool DataService::swapCardViewsInHand(int idx1, int idx2) {
	if(idx1 < 0 || idx1 >= cardViewsInHand.size() || idx2 < 0 || idx2 >= cardViewsInHand.size()) {
		return false; // 索引越界
	}
	std::swap(cardViewsInHand[idx1], cardViewsInHand[idx2]);
	return true;
}