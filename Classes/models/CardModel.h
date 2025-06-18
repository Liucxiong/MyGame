#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "../configs/models/CardResConfig.h" //����ui�����ļ�
#include "../views/CardView.h"
/// <summary>
/// �������ݽṹ
/// </summary>
class CardModel {
private:
	card::CardSuitType suitType;	//��Ƭ��ɫ
	card::CardFaceType faceType;	//���Ƶ���
	bool clickable = false;			//�Ƿ�ɵ��
	int index = 0;					//������ȫ�������е�����
	cocos2d::Vec2 position;			//����λ��
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
	/// ���ؿ��Ƶĵ���ֵ
	/// </summary>
	/// <returns>Int</returns>
	int getCardFaceValue() const {
		return faceType;
	}
	/// <summary>
	/// ��ȡ�ƵĻ�ɫֵ��
	/// </summary>
	/// <returns>�ƵĻ�ɫֵ������Ϊ int��</returns>
	int getCardSuitValue() const {
		return suitType;
	}
};


#endif