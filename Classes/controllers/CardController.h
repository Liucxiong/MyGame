#ifndef __CARD_CONTROLLER_H__
#define __CARD_CONTROLLER_H__

#include "../views/CardView.h"
#include "../services/GameModelFromLevelGenerator.h"
#include "../services/UndoService.h"
#include "../models/CardModel.h"

class CardController
{
private:
	bool isChangingCard = false; // �Ƿ����ڽ�������,�򵥻����ֹ����
public:
	//���Ƶ�������¼�
	// ������
	void onHandCardClicked(CardView* cardView);
	//������
	void onTableCardClicked(CardView* cardView);
	/// <summary>
	/// ����������һ���Ƶ��������򣬲�ִ����Ӧ�Ķ��������Ƶ���ص�����֮һ
	/// </summary>
	/// <param name="index">Ҫ������������±�</param>
	void switchCardInHandToTop(int index);
	/// <summary>
	/// �������ϵ�ָ�������ƶ������ƶ��������Ƶ���ص�����֮��
	/// </summary>
	/// <param name="index">Ҫ�ƶ��Ŀ����������ϵ�������</param>
	void switchCardInTableToHandTop(int index);
	/// <summary>
	/// ���ƺ�����ƥ���߼�
	/// </summary>
	/// <param name="tableIndex">�����±�</param>
	/// <returns>true / false</returns>
	bool isAbleToMatch(int tableIndex) const;
	/// <summary>
	/// �����������������ƽ����������Ĳ�����
	/// </summary>
	/// <param name="idxA">Ҫ�����ĵ�һ�����Ƶ�������</param>
	/// <param name="idxB">Ҫ�����ĵڶ������Ƶ�������</param>
	void undoSwitchCardInHandToTop(int idxA,int idxB);
	/// <summary>
	/// �������е��ƻ��˵�����
	/// </summary>
	/// <param name="idxA">���������������</param>
	/// <param name="idxB">��������Ƭ��������</param>
	void undoSwitchCardInTableToHandTop(int idxA, int idxB);
	/// <summary>
	/// ������һ�β�������Ϊlable�Ļص�����ʹ�á�
	/// </summary>
	void undoLastMove();

};

#endif