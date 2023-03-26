from sample.DataHandler import DataHandler


class Chromosome:
    def __init__(self, params):
        self.__params = params
        self.__representation = [DataHandler.generate_value(
            params['min'], params['max']
        ) for _ in range(params['nodes'])]
        self.__fitness = 0.0

    @property
    def representation(self):
        return self.__representation

    @property
    def fitness(self):
        return self.__fitness

    @representation.setter
    def representation(self, r=None):
        if r is None:
            r = []
        self.__representation = r

    @fitness.setter
    def fitness(self, fitness = 0.0):
        self.__fitness = fitness

    def crossover(self, chromosome):
        r = DataHandler.generate_value(0, len(self.__representation) - 1)
        new_representation = []
        for i in range(r):
            new_representation.append(self.__representation[i])
        for i in range(r, len(self.__representation)):
            new_representation.append(chromosome.representation[i])
        offspring = Chromosome(chromosome.__params)
        offspring.representation = new_representation
        return offspring

    def mutation(self):
        first_gene = DataHandler.generate_value(0, len(self.__representation) - 1)
        second_gene = DataHandler.generate_value(0, len(self.__representation) - 1)
        aux = self.__representation[first_gene]
        self.__representation[first_gene] = self.__representation[second_gene]
        self.__representation[second_gene] = aux

    @staticmethod
    def number_of_components(chromosome):
        components = {}
        for i in chromosome.representation:
            if i in components:
                components[i] += 1
            else:
                components[i] = 1
        return components

    def __str__(self):
        return '\nChromosome: ' + str(self.__representation) + ' has fitness: ' + str(self.__fitness)

    def __repr__(self):
        return self.__str__()

    def __eq__(self, c):
        return self.__representation == c.__representation \
               and self.__fitness == c.__fitness

