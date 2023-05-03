from copy import deepcopy
from random import randint

import utils


class Chromosome:
    """
    Class for representing a Chromosome.
    """

    def __init__(self, params):

        self.__params = params
        self.__no_nodes = params["noNodes"]
        self.__fitness = 0
        self.__values = []

        self.__init_chromo()

    @property
    def params(self):
        return self.__params

    @property
    def no_nodes(self):
        return self.__no_nodes

    @property
    def fitness(self):
        return self.__fitness

    @fitness.setter
    def fitness(self, fit):
        self.__fitness = fit

    @property
    def values(self):
        return self.__values

    @values.setter
    def values(self, val):
        self.__values = val

    def __init_chromo(self):
        """
        Method for initialising the values of the chromosome.
        """

        self.__values = utils.random_perm([i for i in range(0, self.__no_nodes)])

    def order_crossover(self, c):
        """
        Method for performing the Order Crossover.
        :param c: the second parent which takes part in the crossover
        :return: the two resulting offsprings

        """

        pos1 = randint(0, self.__no_nodes - 2)
        pos2 = randint(0, self.__no_nodes - 2)

        if pos2 < pos1:
            pos1, pos2 = pos2, pos1

        values1 = [-1 for _ in range(0, self.__no_nodes)]
        values2 = [-1 for _ in range(0, self.__no_nodes)]

        for i in range(pos1 + 1, pos2 + 1):
            values1[i] = self.__values[i]
            values2[i] = c.values[i]

        for i in range(pos2 + 1, self.__no_nodes):
            j = i
            while c.values[j] in values1:
                j += 1
                if j > self.__no_nodes - 1:
                    j = 0

            values1[i] = c.values[j]

        for i in range(0, pos1 + 1):
            j = i
            while c.values[j] in values1:
                j += 1
                if j > self.__no_nodes - 1:
                    j = 0

            values1[i] = c.values[j]

        for i in range(pos2 + 1, self.__no_nodes):
            j = i
            while self.__values[j] in values2:
                j += 1
                if j > self.__no_nodes - 1:
                    j = 0

            values2[i] = self.__values[j]

        for i in range(0, pos1 + 1):
            j = i
            while self.__values[j] in values2:
                j += 1
                if j > self.__no_nodes - 1:
                    j = 0

            values2[i] = self.__values[j]

        offspring1 = Chromosome(c.params)
        offspring1.values = values1

        offspring2 = Chromosome(c.params)
        offspring2.values = values2

        return offspring1, offspring2

    def mutation(self):
        pos1 = randint(0, self.__no_nodes - 1)

        pos2 = randint(0, self.__no_nodes - 1)
        while pos1 == pos2:
            pos2 = randint(0, self.__no_nodes - 1)

        aux = self.__values[pos1]
        self.__values[pos1] = self.__values[pos2]
        self.__values[pos2] = aux

    def __str__(self):
        """
        Method for returning a string containing the chromosome's data.
        :return: a string containing the chromosome's data

        """

        return " Fitness: " + str(self.__fitness) + "; Cromozom: " + str(self.__values)
