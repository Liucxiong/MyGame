#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "../models/CardModel.h"
#include "../controllers/CardController.h"

/// <summary>
/// GameView ���ʾ��Ϸ����������������ʾ������ͼ����������ص��û�������
/// </summary>
class GameView : public cocos2d::Scene {
private:
	CardController* _controller; // �����������ڹ������Ƶ��߼�
public:
	static GameView* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	//��̬���һ���Ƶ���Ϸ��ͼ��
	void addCard(CardView* view, const cocos2d::Vec2& pos,int type);
	CREATE_FUNC(GameView);
};

#endif