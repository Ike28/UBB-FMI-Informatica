from Repository.file_repository import FileRepository


class Operation:
    def __init__(self, repository: FileRepository):
        self.repository = repository

    def undo(self):
        raise NotImplemented('\nOperation class is only to be used as template.')

    def redo(self):
        raise NotImplemented('\nOperation class is only to be used as template.')
