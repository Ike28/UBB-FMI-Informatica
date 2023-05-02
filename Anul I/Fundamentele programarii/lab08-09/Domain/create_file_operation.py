from Domain.operation import Operation
from Repository.file_repository import FileRepository
import os
from xlsxwriter import Workbook


class CreateExcelFileOperation(Operation):
    def __init__(self, repository: FileRepository, filename):
        super(CreateExcelFileOperation, self).__init__(repository)
        self.__filename = filename

    def undo(self):
        os.remove(self.__filename)

    def redo(self):
        Workbook(self.__filename)

    def strundo(self):
        return f'A fost sters fisierul Excel {self.__filename}.'

    def strredo(self):
        return f'A fost recreat fisierul Excel {self.__filename}.'
