from Domain.entity import Entity


class City(Entity):
    def __init__(self, given_id: str, given_name: str, given_population: int):
        super(City, self).__init__(given_id)
        self.__name = given_name
        self.__population = given_population
        self.__street_names = []

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value: str):
        self.__name = value

    @property
    def population(self):
        return self.__population

    @population.setter
    def population(self, value: int):
        self.__population = value
        
    @property
    def streets(self):
        return self.__street_names
    
    def add_street(self, street: str):
        self.__street_names.append(street)

    def __str__(self):
        return f'ID: {self.id} / Orasul {self.name} are {self.population} locuitori.'
