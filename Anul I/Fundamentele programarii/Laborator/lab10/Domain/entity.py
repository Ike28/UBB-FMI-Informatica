class Entity:
    def __init__(self, given_id):
        self.__id = given_id

    @property
    def id(self):
        return self.__id

    def __eq__(self, other):
        return self.id == other.id
