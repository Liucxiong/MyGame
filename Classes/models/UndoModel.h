#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include <string>

/// <summary>
/// �����˳�������������ö�١�
/// </summary>
enum Undo_Type {
	HAND2HAND = 0,	//��������
	TABLE2HAND = 1,	//���������Ƶ�����
};
/// <summary>
/// ������������ģ���ࡣ
/// </summary>
class UndoModel {
private:
	int indexA;		//�����ĵ�һ��Ԫ�ص�����
	int indexB;		//�����ĵڶ���Ԫ�ص�����
	Undo_Type type; // �޸����� `type` ��������ȷΪ `Undo_Type`
public:
	UndoModel(int a, int b, Undo_Type t) : indexA(a), indexB(b), type(t) {}
	~UndoModel(){}
	int getIndexA() const { return indexA; }
	int getIndexB() const { return indexB; }
	Undo_Type getType() const { return type; }
	bool operator==(const UndoModel& other) const {
		return (indexA == other.indexA && indexB == other.indexB && type == other.type);
	}
	std::string toString() { 
		std::string v = "HAND2HAND";
		if (type == TABLE2HAND) v = "TABLE2HAND";
		return "Type: " + v + " IdxA: " + std::to_string(indexA) + " IdxB: " + std::to_string(indexB);
	}
};

#endif