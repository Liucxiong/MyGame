#ifndef __GAME_MODEL_FROM_LEVEL_GENERATOR_H__
#define __GAME_MODEL_FROM_LEVEL_GENERATOR_H__

#include <map>
#include "../configs/loaders/LevelConfigLoader.h"	//���ؾ�̬����
#include "../models/CardModel.h"

#include "../views/CardView.h"

/// <summary>
/// �ִ����ݷ�����
/// </summary>
class DataService {
private:
	std::map<CardView*, CardModel*> cardView2Model;	//ȫ�ֿ�����ͼ��ģ�͵�ӳ���ϵ
	std::vector<CardView*> cardViewsInTable;	//���濨����ͼ�б�
	std::vector<CardView*> cardViewsInHand;		//���ƿ�����ͼ�б�
public:
    static DataService& get();  // ȫ�ַ�����ڷ��ص�ʵ������

	void InitData();					//��ʼ������

	void addCardToHand(CardView* view);			//��������
	void addCardToTable(CardView* view);		//�������濨��
	//������п���
	void clear();
	//��ȡ����ģ��								
	CardModel* getCardModel(CardView* view);
	//��ȡ���濨������	
	int getCardCountInTable() const;
	//ͨ���±��ȡ���濨����ͼ				
	CardView* getCardViewInTable(int idx);
	//��ȡ�����������һ�ſ�����ͼ		
	CardView* getCardLastViewInTable();
	//ͨ���±��������濨����ͼ		
	bool setCardViewInTable(int idx, CardView* view);	

	//��ȡ���ƿ�������
	int getCardCountInHand() const;
	//ͨ���±��ȡ���ƿ�����ͼ				
	CardView* getCardViewInHand(int idx);
	//��ȡ�������һ�ſ�����ͼ		
	CardView* getCardLastViewInHand();
	//ͨ���±��������ƿ�����ͼ		
	bool setCardViewInHand(int idx, CardView* view);

	//�������濨����ͼλ��	
	bool swapCardViewsInTable(int idx1, int idx2);
	//�������ƿ�����ͼλ��	
	bool swapCardViewsInHand(int idx1, int idx2);	
};

#endif