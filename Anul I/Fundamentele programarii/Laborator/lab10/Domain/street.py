from Domain.entity import Entity


class Street(Entity):
    def __init__(self, given_id, given_city_id, given_name, given_length):
        super(Street, self).__init__(given_id)
        self.__city_id = given_city_id
        self.__name = given_name
        self.__length = given_length

    @property
    def city_id(self):
        return self.__city_id

    @city_id.setter
    def city_id(self, value):
        self.__city_id = value

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    @property
    def length(self):
        return self.__length

    @length.setter
    def length(self, value):
        self.__length = value

    def __str__(self):
        return f'ID: {self.id} / Strada {self.name} din orasul cu id-ul {self.id} are lungimea de {self.length} km'
