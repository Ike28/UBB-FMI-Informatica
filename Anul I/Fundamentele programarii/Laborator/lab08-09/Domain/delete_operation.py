from Domain.operation import Operation
from Repository.file_repository import FileRepository


class DeleteOperation(Operation):
    def __init__(self, repository: FileRepository, deleted_object):
        super(DeleteOperation, self).__init__(repository)
        self.__deleted = deleted_object

    def undo(self):
        self.repository.create(self.__deleted)

    def redo(self):
        self.repository.delete(self.__deleted.id)

    def strundo(self):
        return f'A fost readaugat obiectul:\n{self.__deleted}'

    def strredo(self):
        return f'A fost sters la loc obiectul:\n{self.__deleted}'
