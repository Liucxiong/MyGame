#ifndef __UNDO_SERVICE_H__
#define __UNDO_SERVICE_H__

#include "../models/UndoModel.h"
#include "../views/CardView.h"

/// <summary>
/// 撤销操作服务类
/// </summary>
class UndoService {
private:
	std::stack<UndoModel*> undoStack;
public:
	static UndoService& get();			//单实例

	void InitStack();

	//添加撤销模型到栈顶
	void pushUndoModel(UndoModel* model);
	//弹出栈顶撤销操作对象指针
	void popUndoModel();
	//获取撤销栈顶的对象指针	
	UndoModel* getUndoStackTopModel();
	//获取撤销次数	
	int getUndoStackCount() const;	
};

#endif