from sample.Chromosome import Chromosome
from random import randint


class GeneticAlgorithm:
    def __init__(self, params=None, chromosome_params=None):
        self.__params = params
        self.__population = []
        self.__chromosome_params = chromosome_params

    @property
    def population(self):
        return self.__population

    def initialise(self):
        for _ in range(0, self.__params['population_size']):
            self.__population.append(Chromosome(self.__chromosome_params))

    def evaluate(self):
        for chromosome in self.__population:
            chromosome.fitness = self.__chromosome_params['function'](chromosome.representation,
                                                                      self.__chromosome_params['network'],
                                                                      self.__chromosome_params['degrees'])

    def best_chromosome(self):
        best = self.__population[0]
        for chromosome in self.__population:
            if chromosome.fitness > best.fitness:
                best = chromosome
        return best

    def worst_chromosome(self):
        worst = self.__population[0]
        for chromosome in self.__population:
            if chromosome.fitness < worst.fitness:
                worst = chromosome
        return worst

    def selection(self):
        first_c = randint(0, self.__params['population_size'] - 1)
        second_c = randint(0, self.__params['population_size'] - 1)
        if self.__population[first_c].fitness > self.__population[second_c].fitness:
            return first_c
        else:
            return second_c

    def generation(self):
        if self.__params['strategy'] == 'standard':
            self.__standard_generation()
        elif self.__params['strategy'] == 'steady-state':
            self.__steady_state_generation()
        else:
            self.__elitism_generation()

    def __standard_generation(self):
        new_population = []
        for _ in range(self.__params['population_size']):
            first_c = self.__population[self.selection()]
            second_c = self.__population[self.selection()]
            offspring = first_c.crossover(second_c)
            offspring.mutation()
            new_population.append(offspring)
        self.__population = new_population
        self.evaluate()

    def __elitism_generation(self):
        new_population = [self.best_chromosome()]
        for _ in range(self.__params['population_size'] - 1):
            first_c = self.__population[self.selection()]
            second_c = self.__population[self.selection()]
            offspring = first_c.crossover(second_c)
            offspring.mutation()
            new_population.append(offspring)
        self.__population = new_population
        self.evaluate()

    def __steady_state_generation(self):
        for _ in range(self.__params['population_size']):
            first_c = self.__population[self.selection()]
            second_c = self.__population[self.selection()]
            offspring = first_c.crossover(second_c)
            offspring.mutation()
            offspring.fitness = self.__chromosome_params['function'](offspring.representation,
                                                                     self.__chromosome_params['network'],
                                                                     self.__chromosome_params['degrees'])
            worst = self.worst_chromosome()
            if offspring.fitness > worst.fitness:
                for i in range(self.__params['population_size']):
                    if self.__population[i] == worst:
                        self.__population[i] = offspring
                        break
