#ifndef __UNDO_SERVICE_H__
#define __UNDO_SERVICE_H__

#include "../models/UndoModel.h"
#include "../views/CardView.h"

/// <summary>
/// ��������������
/// </summary>
class UndoService {
private:
	std::stack<UndoModel*> undoStack;
public:
	static UndoService& get();			//��ʵ��

	void InitStack();

	//��ӳ���ģ�͵�ջ��
	void pushUndoModel(UndoModel* model);
	//����ջ��������������ָ��
	void popUndoModel();
	//��ȡ����ջ���Ķ���ָ��	
	UndoModel* getUndoStackTopModel();
	//��ȡ��������	
	int getUndoStackCount() const;	
};

#endif