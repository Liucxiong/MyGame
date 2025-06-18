#include "CardController.h"
#include "../views/GameView.h"
USING_NS_CC;

//type = 0ʱ���� ��ʾ���������
void CardController::onHandCardClicked(CardView* cardView) {
	if (!cardView || isChangingCard) { CCLOG("IS Changing!!!!"); return; }
	else {
		isChangingCard = true;
		CCLOG("Hand Card was clicked at position: (%f, %f)", cardView->getPositionX(), cardView->getPositionY());
	}
	int idx = DataService::get().getCardModel(cardView)->getIndex();
    // �����ƶ�
	switchCardInHandToTop(idx);
}

//type = 1ʱ���� ��ʾ�����������
void CardController::onTableCardClicked(CardView* cardView) {
	if (!cardView || isChangingCard) { CCLOG("IS Changing!!!!"); return; }
	else {
		isChangingCard = true;
        CCLOG("Table Card was clicked at position: (%f, %f)", cardView->getPositionX(), cardView->getPositionY());
    }
	int idx = DataService::get().getCardModel(cardView)->getIndex();
	// �����ƶ�
	if (isAbleToMatch(idx)) switchCardInTableToHandTop(idx);	//�ɹ�ִ�л��ƶ���
	else {
		cardView->cardShake();		//���ƶ���
		DataService::get().getCardLastViewInHand()->cardShake(); //����Ҳ��һ��
		isChangingCard = false;
	}
}

void CardController::switchCardInHandToTop(int index) {
    // ��������λ��
	DataService data = DataService::get();
	CardView* cardA = data.getCardViewInHand(index);
    CardView* cardB = data.getCardLastViewInHand();
	CardModel* modelA = data.getCardModel(cardA);
	CardModel* modelB = data.getCardModel(cardB);
	if (!cardA || !cardB || !modelA || !modelB) { isChangingCard = false; return; }
    // ��ȡ��ǰ����λ��
    Vec2 posModel = modelA->getPosition();
	Vec2 posA = cardA->getPosition();
    Vec2 posB = cardB->getPosition();
 
    //����
    auto move = MoveTo::create(0.3f, posB);
    auto finish = CallFunc::create([=]() {
		modelA->setPosition(modelB->getPosition());
		modelA->setClickable(false);
		modelA->setIndex(data.getCardCountInHand() - 1);

		modelB->setPosition(posModel);
		modelB->setClickable(true);
		modelB->setIndex(index);
        
		cardA->setClickable(false);
        // ����Z��˳��ȷ�������ϲ㣬+ 2���ⱻ��������
		cardA->setLocalZOrder(modelA->getIndex() + 2);  
        
		// ����cardB��λ�úͿɵ��״̬
		cardB->setClickable(true);
        cardB->setPosition(posA);
		cardB->setLocalZOrder(modelB->getIndex() + 2);

		DataService::get().swapCardViewsInHand(index, data.getCardCountInHand() - 1);
		//��¼������¼
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
    // ��ȡ��ǰ����λ��
	Vec2 posModel = modelB->getPosition();
    Vec2 posB = cardB->getPosition();
	Vec2 posA = cardA->getPosition();

	auto move = MoveTo::create(0.3f, posB);
    auto finish = CallFunc::create([=]() {
		//cardB->retain();
		//cardB->removeFromParent();	//�Ƴ�Ԫ��
		cardB->setVisible(false);	//����Ԫ��
		//ֻ��Ҫ����A��Ƭ�ľ���λ��������Ϣ�������ڻָ�
		modelB->setPosition(modelA->getPosition());
		modelB->setClickable(false);
		modelB->setIndex(index);
		cardB->setPosition(posA);
		//��ƬB�Ļص���������

        modelA->setPosition(posModel);
        modelA->setIndex(data.getCardCountInHand() - 1);
		modelA->setClickable(false);

        cardA->setClickable(false);
		cardA->setLocalZOrder(modelA->getIndex() + 2);  // ȷ�������ϲ㣬+ 2���ⱻ��������
        //�޸Ļص�����
        cardA->setClickCallback([this](CardView* sender) {
            onHandCardClicked(sender);
            });
		//�������ƺ�������
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
	CardView* cardA = data.getCardViewInTable(idxA);	//��ȡ������A
	CardView* cardB = data.getCardViewInHand(idxB);		//��ȡ����B
	CardModel* modelA = data.getCardModel(cardA);	
	CardModel* modelB = data.getCardModel(cardB);	
	if (!cardA || !cardB || !modelA || !modelB) { isChangingCard = false; return; }
	Vec2 posA = cardA->getPosition();	
	Vec2 posB = cardB->getPosition();	
	Vec2 posModel = modelA->getPosition();

	auto move = MoveTo::create(0.3f, posA);
	auto finish = CallFunc::create([=]() {
		modelA->setPosition(modelB->getPosition());	//��A��Ƭ��ģ��λ������ΪB��Ƭ��ģ��λ��
		modelA->setClickable(false);
		modelA->setIndex(idxB);	//��A��Ƭ����������Ϊ���Ƶ����һ��
		cardA->setVisible(true);	//��B��Ƭ�Ŀɼ�������Ϊtrue
		cardA->setPosition(posB);	//��A��Ƭ��λ������ΪB��Ƭ�����½�λ��
		cardA->setLocalZOrder(idxB + 2);	//��A��Ƭ��Z��˳������ΪB��Ƭ������+2��ȷ�������ϲ�
		cardA->setClickable(false);	//��A��Ƭ�Ŀɵ��������Ϊfalse

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