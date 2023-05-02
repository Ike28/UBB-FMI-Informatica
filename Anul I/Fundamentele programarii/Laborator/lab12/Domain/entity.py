class Entity:
    """
    Descrie o clasa generica de obiecte entitate, caracterizate prin ID
    """
    def __init__(self, given_id):
        self.__id = given_id

    @property
    def id(self):
        return self.__id

    def __eq__(self, other):
        return self.id == other.id
