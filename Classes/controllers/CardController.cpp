#include "CardController.h"
#include "../views/GameView.h"
USING_NS_CC;

//type = 0时调用 表示点击了手牌
void CardController::onHandCardClicked(CardView* cardView) {
	if (!cardView || isChangingCard) { CCLOG("IS Changing!!!!"); return; }
	else {
		isChangingCard = true;
		CCLOG("Hand Card was clicked at position: (%f, %f)", cardView->getPositionX(), cardView->getPositionY());
	}
	int idx = DataService::get().getCardModel(cardView)->getIndex();
    // 动画移动
	switchCardInHandToTop(idx);
}

//type = 1时调用 表示点击了桌面牌
void CardController::onTableCardClicked(CardView* cardView) {
	if (!cardView || isChangingCard) { CCLOG("IS Changing!!!!"); return; }
	else {
		isChangingCard = true;
        CCLOG("Table Card was clicked at position: (%f, %f)", cardView->getPositionX(), cardView->getPositionY());
    }
	int idx = DataService::get().getCardModel(cardView)->getIndex();
	// 动画移动
	if (isAbleToMatch(idx)) switchCardInTableToHandTop(idx);	//成功执行换牌动作
	else {
		cardView->cardShake();		//卡牌抖动
		DataService::get().getCardLastViewInHand()->cardShake(); //手牌也震动一下
		isChangingCard = false;
	}
}

void CardController::switchCardInHandToTop(int index) {
    // 交换手牌位置
	DataService data = DataService::get();
	CardView* cardA = data.getCardViewInHand(index);
    CardView* cardB = data.getCardLastViewInHand();
	CardModel* modelA = data.getCardModel(cardA);
	CardModel* modelB = data.getCardModel(cardB);
	if (!cardA || !cardB || !modelA || !modelB) { isChangingCard = false; return; }
    // 获取当前手牌位置
    Vec2 posModel = modelA->getPosition();
	Vec2 posA = cardA->getPosition();
    Vec2 posB = cardB->getPosition();
 
    //动画
    auto move = MoveTo::create(0.3f, posB);
    auto finish = CallFunc::create([=]() {
		modelA->setPosition(modelB->getPosition());
		modelA->setClickable(false);
		modelA->setIndex(data.getCardCountInHand() - 1);

		modelB->setPosition(posModel);
		modelB->setClickable(true);
		modelB->setIndex(index);
        
		cardA->setClickable(false);
        // 设置Z轴顺序，确保在最上层，+ 2避免被背景覆盖
		cardA->setLocalZOrder(modelA->getIndex() + 2);  
        
		// 更新cardB的位置和可点击状态
		cardB->setClickable(true);
        cardB->setPosition(posA);
		cardB->setLocalZOrder(modelB->getIndex() + 2);

		DataService::get().swapCardViewsInHand(index, data.getCardCountInHand() - 1);
		//记录交换记录
		UndoModel* undoModel = new UndoModel(index,data.getCardCountInHand() - 1,HAND2HAND);
		UndoService::get().pushUndoModel(undoModel);

		isChangingCard = false;
        });

    cardA->runAction(Sequence::create(move, finish, nullptr));
}

void CardController::switchCardInTableToHandTop(int index) {
	DataService data = DataService::get();
    CardView* cardA = data.getCardViewInTable(index);
	CardView* cardB = data.getCardLastViewInHand();
	CardModel* modelA = data.getCardModel(cardA);
	CardModel* modelB = data.getCardModel(cardB);
	if (!cardA || !cardB || !modelA || !modelB) { isChangingCard = false; return; }
    // 获取当前手牌位置
	Vec2 posModel = modelB->getPosition();
    Vec2 posB = cardB->getPosition();
	Vec2 posA = cardA->getPosition();

	auto move = MoveTo::create(0.3f, posB);
    auto finish = CallFunc::create([=]() {
		//cardB->retain();
		//cardB->removeFromParent();	//移除元素
		cardB->setVisible(false);	//隐藏元素
		//只需要记下A卡片的具体位置数据信息即可用于恢复
		modelB->setPosition(modelA->getPosition());
		modelB->setClickable(false);
		modelB->setIndex(index);
		cardB->setPosition(posA);
		//卡片B的回调函数不变

        modelA->setPosition(posModel);
        modelA->setIndex(data.getCardCountInHand() - 1);
		modelA->setClickable(false);

        cardA->setClickable(false);
		cardA->setLocalZOrder(modelA->getIndex() + 2);  // 确保在最上层，+ 2避免被背景覆盖
        //修改回调函数
        cardA->setClickCallback([this](CardView* sender) {
            onHandCardClicked(sender);
            });
		//交换手牌和桌面牌
        DataService::get().setCardViewInHand(modelA->getIndex(), cardA);
        DataService::get().setCardViewInTable(index, cardB);

		UndoModel* undoModel = new UndoModel(index, data.getCardCountInHand() - 1, TABLE2HAND);
		UndoService::get().pushUndoModel(undoModel);
		isChangingCard = false;
        });
	cardA->runAction(Sequence::create(move, finish, nullptr));
}

bool CardController::isAbleToMatch(int tableIndex) const {
	DataService& data = DataService::get();
	CardView* card = data.getCardViewInTable(tableIndex);
	CardView* topCard = data.getCardLastViewInHand();
	if (!card || !topCard) return false;
	int cardValue = data.getCardModel(card)->getCardFaceValue();
	int topCardValue = data.getCardModel(topCard)->getCardFaceValue();
	int ma = std::max(cardValue, topCardValue), mi = std::min(cardValue, topCardValue);
	CCLOG("Card Value: %d, Top Card Value: %d, Max: %d, Min: %d", cardValue, topCardValue, ma, mi);
	if ((mi + 1) % card::totalCardFaceNumer == ma || (ma + 1) % card::totalCardFaceNumer == mi) return true;
	else return false;
}


void CardController::undoLastMove() {
	UndoService& undoService = UndoService::get();
	if(isChangingCard || undoService.getUndoStackCount() == 0) {
		CCLOG("Cannot undo while changing card Or don not have steps.");
		return;
	}
	isChangingCard = true;
	
	UndoModel* undo = undoService.getUndoStackTopModel();
	CCLOG("Undoing last move: %s", undo->toString().c_str());
	switch (undo->getType())
	{
	case HAND2HAND: {
		undoSwitchCardInHandToTop(undo->getIndexA(), undo->getIndexB()); 
		undoService.popUndoModel();
		delete undo;
		break;
	}
	case TABLE2HAND: {
		CCLOG("Want To Recover T to H\n");
		undoSwitchCardInTableToHandTop(undo->getIndexA(), undo->getIndexB());
		undoService.popUndoModel();
		delete undo;
		break;
	}
	default:
		break;
	}
	CCLOG("Now Have: %d Steps could be restored, clicked to reset\n", UndoService::get().getUndoStackCount());
}

void CardController::undoSwitchCardInHandToTop(int idxA, int idxB) {
	DataService& data = DataService::get();
	CardView* cardA = data.getCardViewInHand(idxA);
	CardView* cardB = data.getCardViewInHand(idxB);
	CardModel* modelA = data.getCardModel(cardA);
	CardModel* modelB = data.getCardModel(cardB);
	if (!cardA || !cardB || !modelA || !modelB) { isChangingCard = false; return; }
	Vec2 posA = cardA->getPosition();
	Vec2 posB = cardB->getPosition();
	Vec2 modelpos = modelA->getPosition();

	auto move = MoveTo::create(0.3f, posA);
	auto finish = CallFunc::create([=]() {
		modelA->setPosition(modelB->getPosition());
		modelA->setClickable(false);
		modelA->setIndex(idxB);
		modelB->setPosition(modelpos);
		modelB->setClickable(true);
		modelB->setIndex(idxA);
		cardA->setPosition(posB);
		cardA->setClickable(false);
		cardA->setLocalZOrder(idxB + 2);

		cardB->setClickable(true);
		cardB->setLocalZOrder(idxA + 2);
		DataService::get().swapCardViewsInHand(idxA, idxB);
		isChangingCard = false;
		});
	cardB->runAction(Sequence::create(move, finish, nullptr));
}

void CardController::undoSwitchCardInTableToHandTop(int idxA, int idxB) {
	DataService& data = DataService::get();
	CardView* cardA = data.getCardViewInTable(idxA);	//获取桌面牌A
	CardView* cardB = data.getCardViewInHand(idxB);		//获取手牌B
	CardModel* modelA = data.getCardModel(cardA);	
	CardModel* modelB = data.getCardModel(cardB);	
	if (!cardA || !cardB || !modelA || !modelB) { isChangingCard = false; return; }
	Vec2 posA = cardA->getPosition();	
	Vec2 posB = cardB->getPosition();	
	Vec2 posModel = modelA->getPosition();

	auto move = MoveTo::create(0.3f, posA);
	auto finish = CallFunc::create([=]() {
		modelA->setPosition(modelB->getPosition());	//将A卡片的模型位置设置为B卡片的模型位置
		modelA->setClickable(false);
		modelA->setIndex(idxB);	//将A卡片的索引设置为手牌的最后一个
		cardA->setVisible(true);	//将B卡片的可见性设置为true
		cardA->setPosition(posB);	//将A卡片的位置设置为B卡片的左下角位置
		cardA->setLocalZOrder(idxB + 2);	//将A卡片的Z轴顺序设置为B卡片的索引+2，确保在最上层
		cardA->setClickable(false);	//将A卡片的可点击性设置为false

		modelB->setPosition(posModel);
		modelB->setIndex(idxA);
		modelB->setClickable(true);
		cardB->setClickable(true);
		cardB->setLocalZOrder(idxA + 2);
		cardB->setClickCallback([this](CardView* sender) {
			onTableCardClicked(sender);
			});
		DataService::get().setCardViewInHand(idxB, cardA);
		DataService::get().setCardViewInTable(idxA, cardB);
		isChangingCard = false;
		});
	cardB->runAction(Sequence::create(move, finish, nullptr));
}