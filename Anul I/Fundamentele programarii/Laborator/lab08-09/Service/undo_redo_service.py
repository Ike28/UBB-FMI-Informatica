from Domain.operation import Operation


class UndoRedoService:
    def __init__(self):
        self.__undo_stack = []
        self.__redo_stack = []

    @property
    def undo_stack(self):
        return self.__undo_stack

    @property
    def redo_stack(self):
        return self.__redo_stack

    def add_undo(self, given_op: Operation):
        self.__undo_stack.append(given_op)
        self.__redo_stack = []

    def undo(self):
        operation = self.__undo_stack.pop()
        self.__redo_stack.append(operation)
        operation.undo()

    def redo(self):
        operation = self.__redo_stack.pop()
        self.__undo_stack.append(operation)
        operation.redo()
