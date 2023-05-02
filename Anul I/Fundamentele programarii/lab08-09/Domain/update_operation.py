from Domain.operation import Operation
from Repository.file_repository import FileRepository


class UpdateOperation(Operation):
    def __init__(self, repository: FileRepository, original_object, updated_object):
        super(UpdateOperation, self).__init__(repository)
        self.__original = original_object
        self.__updated = updated_object

    def undo(self):
        self.repository.update(self.__original)

    def redo(self):
        self.repository.update(self.__updated)

    def strundo(self):
        return f'A fost restaurat obiectul:\n{self.__updated}\nla starea initiala:\n{self.__original}'

    def strredo(self):
        return f'A fost recalibrat obiectul:\n{self.__original}\nla datele noi:\n{self.__updated}'
