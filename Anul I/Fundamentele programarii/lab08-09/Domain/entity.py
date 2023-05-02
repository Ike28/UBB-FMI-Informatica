class Entity:
    """
    Descrie o entitate generica cu id
    """

    def __init__(self, given_id=None):
        """
        Creeaza un obiect de tip Entitate generica
        :param given_id: id-ul entitatii
        """
        self.__id = given_id

    @property
    def id(self):
        return self.__id

    @id.setter
    def id(self, value):
        self.__id = value

    def __eq__(self, other):
        return type(self) == type(other) and self.id == other.id
