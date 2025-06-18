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
	//�������Ƴ�ʼ����
	for (const auto& i : tableModel) {
		auto view = CardView::createCard(i->getFaceType(), i->getSuitType());
		view->setClickable(true);
		view->setLocalZOrder(i->getIndex() + 2); // ���ñ��� Z ˳��
		cardView2Model[view] = i;
		cardViewsInTable.emplace_back(view);
	}
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	//�������Ƴ�ʼ����,λ�������Զ�����
	for (auto& i : handModel) {
		auto view = CardView::createCard(i->getFaceType(), i->getSuitType());
		i->setPosition(cocos2d::Vec2(visibleSize.width * 0.14 + 0.8 * view->getContentSize().width * i->getIndex(),
			visibleSize.height * 0.1f)); // �������ƶѵ�����Ƭ����
		view->setClickable(true);
		view->setLocalZOrder(i->getIndex() + 2); // ���ñ��� Z ˳��
		cardView2Model[view] = i;
		cardViewsInHand.emplace_back(view);
	}
	//���������һ�������б����������ƶ�������
	CardView* endView = cardViewsInHand.back();
	CardModel* endModel = cardView2Model[endView];
	endModel->setClickable(false); endView->setClickable(false);
	endModel->setPosition(cocos2d::Vec2(visibleSize.width * 0.6,
		visibleSize.height * 0.1f)); // �������ƶѵ�����Ƭ����
}

void DataService::addCardToHand(CardView* view) {
	cardViewsInHand.emplace_back(view);
}

void DataService::addCardToTable(CardView* view) {
	cardViewsInTable.emplace_back(view);
}

void DataService::clear() {
	// �ͷ� CardView�������û�б� Cocos �ĳ������йܣ�
	for (auto view : cardViewsInHand) {
		if (view->getParent()) {
			view->removeFromParent(); // ֻ�Ƴ�����ɾ��
		}
		else {
			delete view; // ������Լ� new �����ġ�δ���� Cocos �й�
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

	// ɾ�� CardModel�����ֶ� new �ģ�һ��Ҫ�ͷţ�
	for (auto& pair : cardView2Model) {
		delete pair.second;
	}

	// �������
	cardViewsInHand.clear();
	cardViewsInTable.clear();
	cardView2Model.clear();
}

CardModel* DataService::getCardModel(CardView* view) {
	return cardView2Model[view];
}
// ��ȡ�������Ŀ�������
int DataService::getCardCountInTable() const {
	return cardViewsInTable.size();
}

CardView* DataService::getCardViewInTable(int idx) {
	if (idx < 0 || idx >= cardViewsInTable.size()) {
		return nullptr; // ����Խ��
	}
	return cardViewsInTable[idx];
}

CardView* DataService::getCardLastViewInTable() {
	if(cardViewsInTable.empty()) {
		return nullptr; // ���������û�п���
	}
	return cardViewsInTable.back(); // ���û���ҵ���Ӧ�� CardView
}

bool DataService::setCardViewInTable(int idx, CardView* view) {
	if (idx < 0 || idx >= cardViewsInTable.size()) {
		return false; // ����Խ��
	}
	cardViewsInTable[idx] = view;
	return true;
}

// ��ȡ�������Ŀ�������
int DataService::getCardCountInHand() const {
	return cardViewsInHand.size();
}

CardView* DataService::getCardViewInHand(int idx) {
	if (idx < 0 || idx >= cardViewsInHand.size()) {
		return nullptr; // ����Խ��
	}
	return cardViewsInHand[idx];
}

CardView* DataService::getCardLastViewInHand() {
	if(cardViewsInHand.empty()) {
		return nullptr; // ���������û�п���
	}
	return cardViewsInHand.back(); // �������������һ�ſ��Ƶ���ͼ
}

bool DataService::setCardViewInHand(int idx, CardView* view) {
	if (idx < 0 || idx >= cardViewsInHand.size()) {
		return false; // ����Խ��
	}
	cardViewsInHand[idx] = view;
	return true;
}

bool DataService::swapCardViewsInTable(int idx1, int idx2) {
	if(idx1 < 0 || idx1 >= cardViewsInTable.size() || idx2 < 0 || idx2 >= cardViewsInTable.size()) {
		return false; // ����Խ��
	}
	std::swap(cardViewsInTable[idx1], cardViewsInTable[idx2]);
	return true;
}

bool DataService::swapCardViewsInHand(int idx1, int idx2) {
	if(idx1 < 0 || idx1 >= cardViewsInHand.size() || idx2 < 0 || idx2 >= cardViewsInHand.size()) {
		return false; // ����Խ��
	}
	std::swap(cardViewsInHand[idx1], cardViewsInHand[idx2]);
	return true;
}