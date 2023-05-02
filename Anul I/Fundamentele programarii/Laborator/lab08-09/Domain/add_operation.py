from Domain.operation import Operation
from Repository.file_repository import FileRepository


class AddOperation(Operation):
    def __init__(self, repository: FileRepository, added_object):
        super(AddOperation, self).__init__(repository)
        self.__added = added_object

    def undo(self):
        self.repository.delete(self.__added.id)

    def redo(self):
        self.repository.create(self.__added)

    def strundo(self):
        return f'A fost anulata creearea obiectului:\n{self.__added}'

    def strredo(self):
        return f'A fost readaugat obiectul:\n{self.__added}'
