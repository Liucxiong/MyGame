#include "UndoService.h"

UndoService& UndoService::get() {
	static UndoService instance;
	return instance;
}

void UndoService::InitStack() {
	undoStack = std::stack<UndoModel*>();
}


void UndoService::pushUndoModel(UndoModel* model) {
	if(model) {
		undoStack.push(model);
	}
}

void UndoService::popUndoModel() {
	if(undoStack.empty()) {
		return;
	}
	undoStack.pop();
}

UndoModel* UndoService::getUndoStackTopModel() {
	if(undoStack.empty()) {
		return nullptr;
	}
	return undoStack.top();
}

int UndoService::getUndoStackCount() const {
	return undoStack.size();
}