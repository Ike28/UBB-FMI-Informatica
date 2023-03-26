import os
import unittest
from parameterized import parameterized
from sample.GeneticAlgorithm import GeneticAlgorithm
from sample.DataHandler import DataHandler
from sample.Chromosome import Chromosome
from definitions import ROOT_DIR


class TestCommunityFinder(unittest.TestCase):
    @parameterized.expand([
        ['dolphins', 'dolphins', 60, 50, 'elitism', 26],
        ['football', 'football', 20, 20, 'steady-state', 58],
        ['krebs', 'krebs', 50, 50, 'elitism', 49]
    ])
    def test_find_communities(self, dirname, filename, population_size, number_of_generations, strategy, expected):
        os.chdir("{}/setup/real/{}".format(ROOT_DIR, dirname))
        graph, degrees = DataHandler.read_data(filename, log_progress=False)
        ga_params = {'population_size': population_size, 'generations': number_of_generations, 'strategy': strategy}
        chromosome_params = {'min': 0, 'max': graph.number_of_nodes(), 'function': DataHandler.modularity,
                             'nodes': graph.number_of_nodes(), 'network': graph, 'degrees': degrees}
        ga = GeneticAlgorithm(ga_params, chromosome_params)
        ga.initialise()
        ga.evaluate()

        for _ in range(ga_params['generations']):
            ga.generation()
        self.assertAlmostEqual(expected, len(Chromosome.number_of_components(ga.best_chromosome()).values()), delta=15)
