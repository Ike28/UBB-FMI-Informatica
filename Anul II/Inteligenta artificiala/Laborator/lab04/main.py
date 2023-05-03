from copy import deepcopy
from datetime import datetime

import utils
from algorithm import GA


def test(graph_name, pop_size, no_generations, expected_result, shortest_path=False, source_node=None, dest_node=None):
    """
    Method used for running a test.
    :param graph_name: the name of the graph
    :param pop_size: the size of the population (number of chromosomes in a populations)
    :param no_generations: the number of generations
    :param expected_result: the expected result
    """

    print("\nRunning tests for " + graph_name + "...")

    last, fit, generation, generations = run_algorithm(graph_name, pop_size, no_generations, shortest_path, source_node, dest_node)

    print("\nThe found sequence of vertices is: " + str(last))
    print("Expected fitness: " + str(expected_result))
    print("Actual fitness: " + str(int(fit)))
    print("Fitness found at generation: " + str(generation))
    print("All generations with that fitness: " + str(generations))

    if int(fit) <= expected_result:
        print("\nGood solution found!")
    else:
        print("\nWorse solution found!")

    print("Difference between solutions is: " + str(abs(int(fit) - expected_result)))


def run_all_tests():
    """
    Method used for running all the tests.
    """

    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    print("\nTests started at: " + str(current_time))

    test("small1", 100, 100, 8)
    test("small2", 100, 100, 16)
    test("small3", 100, 100, 97)
    test("small4", 100, 100, 8)
    test("small5", 100, 100, 38)

    test("medium1", 100, 100, 8)
    test("medium2", 100, 100, 7)
    test("medium3", 100, 100, 35)
    test("medium4", 100, 100, 40)

    test("small1_non_complete", 100, 100, 79)
    test("small2_non_complete", 100, 100, 52)
    test("small3_non_complete", 100, 100, 5)
    test("small4_non_complete", 100, 100, 6)

    test("gr17", 1000, 500, 2085)
    test("gr21", 1000, 500, 2707)
    test("gr24", 1000, 1000, 1272)

    test("ulysses16", 500, 500, 6859)
    test("ulysses22", 1000, 1000, 7013)

    test("burma14", 1000, 1000, 3323)
    test("fri26", 1000, 1000, 937)

    now = datetime.now()
    current_time = now.strftime("%H:%M:%S")
    print("\nTests finished at at: " + str(current_time))


def run_all_tests_shortest_path():

    print("\n\nRunning tests for shortest paths...\n")

    test("small1", 10, 10, 1, True, 2, 4)
    test("small6", 10, 10, 3, True, 1, 3)
    test("small2", 10, 10, 2, True, 2, 3)
    test("small2", 10, 10, 5, True, 0, 3)

    test("small2_non_complete", 10, 10, 20, True, 0, 1)
    test("small2_non_complete", 10, 10, 20, True, 1, 0)

    test("medium4", 10, 10, 5, True, 0, 3)
    test("medium4", 10, 10, 5, True, 1, 4)


def run_algorithm(graph_name, pop_size, no_generations, shortest_path=False, source_node=None, dest_node=None):
    """
    Method used for running the algorithm.
    :param graph_name: the name of the graph
    :param pop_size: the size of the population (i.e. the number of chromosomes in a population)
    :param no_generations: the number of generations
    :param shortest_path: True - if the algorithm will be run in the shortest_path mode; False - otherwise
    :param source_node: the source node of the shortest path
    :param dest_node: the destination node of the shortest path
    :return: max_last: the first chromosome for which the best fitness was obtained;
            max_fit: the best fitness which was obtained;
            max_gen: the generation number of the generation in which the best chromosome was obtained;
            max_generations: all of the generations found with the best fitness
    """

    network = utils.parse_xml(graph_name)

    print("Average edge cost: " + str(network["edgeAvg"]))

    algo_params = {"popSize": pop_size, "noGenerations": no_generations, "network": network, "pc": 0.8, "pm": 0.1,
                   "shortestPath": shortest_path, "spFrom": source_node, "spTo": dest_node}

    chromosome_params = {"noNodes": network["noNodes"]}

    ga = GA(algo_params, chromosome_params)
    ga.initialise()
    ga.evaluate()

    max_last = []
    max_fit = network["weightSum"]
    max_generations = []
    max_gen = 0

    i = 0
    for generation in range(0, algo_params["noGenerations"]):
        ga.one_generation_elitism()

        best_chromosome = ga.best_chromosome()

        last = best_chromosome.values
        fit = best_chromosome.fitness

        if fit < max_fit:
            max_fit = fit
            max_last = deepcopy(last)
            max_gen = generation
            max_generations = [last]

        elif fit == max_fit:
            if last not in max_generations:
                max_generations.append(last)

        i += 1

    return max_last, max_fit, max_gen, max_generations


run_all_tests()
run_all_tests_shortest_path()
