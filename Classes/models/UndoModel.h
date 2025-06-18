#ifndef __UNDO_MODEL_H__
#define __UNDO_MODEL_H__

#include <string>

/// <summary>
/// 定义了撤销操作的类型枚举。
/// </summary>
enum Undo_Type {
	HAND2HAND = 0,	//交换手牌
	TABLE2HAND = 1,	//将桌面牌移到手牌
};
/// <summary>
/// 撤销操作数据模型类。
/// </summary>
class UndoModel {
private:
	int indexA;		//交换的第一个元素的索引
	int indexB;		//交换的第二个元素的索引
	Undo_Type type; // 修复：将 `type` 的类型明确为 `Undo_Type`
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