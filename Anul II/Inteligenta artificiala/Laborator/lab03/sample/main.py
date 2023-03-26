from sample.UserInterface import *
from sample.DataHandler import DataHandler
from sample.GeneticAlgorithm import GeneticAlgorithm
from sample.Chromosome import Chromosome


def main():
    settings = UserInterface.read_configuration()
    if settings is None:
        return

    target_file = settings[0]
    file_type = settings[1]

    graph, degrees = DataHandler.read_data(target_file, file_type=file_type)
    ga_params, chromosome_params = UserInterface.read_ga_params(graph, degrees)
    generations = []
    ga = GeneticAlgorithm(ga_params, chromosome_params)
    ga.initialise()
    ga.evaluate()
    best_chromosome = ga.best_chromosome()

    for generation in range(ga_params['generations']):
        generations.append(generation)
        ga.generation()
        best_chromosome = ga.best_chromosome()
        print('generation: ' + str(generation) + "; number of communities: "
              + str(len(Chromosome.number_of_components(best_chromosome).values()))
              + "; x = " + str(best_chromosome.representation) + " fitness = "
              + str(best_chromosome.fitness))
    print("number of communities: ", str(len(Chromosome.number_of_components(best_chromosome).values())))


if __name__ == "__main__":
    main()
