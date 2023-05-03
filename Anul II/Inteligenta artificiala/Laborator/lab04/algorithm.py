from random import randint, uniform

import utils
from chromosome import Chromosome


class GA:
    """
    Class for the Genetic Algorithm (GA).
    """

    def __init__(self, params, chromo_params):
        self.__pop_size = params["popSize"]
        self.__no_generations = params["noGenerations"]
        self.__network = params["network"]
        self.__shortest_path = params["shortestPath"]
        self.__sp_from = params["spFrom"]
        self.__sp_to = params["spTo"]
        self.__chromo_params = chromo_params
        self.__population = []
        self.__pc = params["pc"]
        self.__pm = params["pm"]

    @property
    def population(self):
        return self.__population

    def initialise(self):
        """
        Method used for initialising the population.
        """

        for _ in range(0, self.__pop_size):
            c = Chromosome(self.__chromo_params)
            self.__population.append(c)

    def evaluate_one(self, chromosome):
        """
        Method used for evaluating the fitness of the given chromosome.
        :param chromosome: the chromosome for which the fitness will be calculated
        """

        chromosome.fitness = utils.calc_fitness(chromosome.values, self.__network, self.__shortest_path, self.__sp_from, self.__sp_to)

    def evaluate(self):
        """
        Method used for evaluating the fitness of all of the chromosomes in the population.
        """

        for chromosome in self.__population:
            chromosome.fitness = utils.calc_fitness(chromosome.values, self.__network, self.__shortest_path, self.__sp_from, self.__sp_to)

    def best_chromosome(self):
        """
        Method used for returning the best chromosome (i.e. the one with the best fitness) in the population.
        :return: the best chromosome in the population
        """

        best = self.__population[0]

        for chromosome in self.__population:
            if chromosome.fitness < best.fitness:
                best = chromosome

        return best

    def worst_chromosome(self):
        """
        Method used for returning the worst chromosome (i.e. the one with the worst fitness) in the population.
        :return: the worst chromosome in the population
        """

        worst = self.__population[0]

        for chromosome in self.__population:
            if chromosome.fitness > worst.fitness:
                worst = chromosome

        return worst

    def selection(self):
        """
        Method used for selecting the positions for a random chromosome in the population.
        :return: the position for a random chromosome in the population
        """

        pos1 = randint(0, self.__pop_size - 1)
        pos2 = randint(0, self.__pop_size - 1)

        if self.__population[pos1].fitness < self.__population[pos2].fitness:
            return pos1

        else:
            return pos2

    def one_generation_elitism(self):
        """
        Method used for obtaining a new generation, using the survival of the fittest method.
        """

        new_pop = [self.best_chromosome()]

        for _ in range(self.__pop_size - 1):
            parent1 = self.__population[self.selection()]
            parent2 = self.__population[self.selection()]

            crossover_prob = uniform(0, 1)
            if crossover_prob <= self.__pc:
                offspring = parent1.order_crossover(parent2)

                self.evaluate_one(offspring[0])
                self.evaluate_one(offspring[1])

                if offspring[0].fitness < offspring[1].fitness:
                    offspring = offspring[0]

                else:
                    offspring = offspring[1]

            else:
                if parent1.fitness > parent2.fitness:
                    offspring = parent2

                else:
                    offspring = parent1

            mutation_prob = uniform(0, 1)
            if mutation_prob <= self.__pm:
                offspring.mutation()

            new_pop.append(offspring)

        self.__population = new_pop
        self.evaluate()
