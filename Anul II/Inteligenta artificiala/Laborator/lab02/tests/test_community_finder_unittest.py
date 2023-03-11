import os
import unittest
from parameterized import parameterized
from sample.DataHandler import *
from sample.CommunityFinder import *
from definitions import ROOT_DIR


class TestCommunityFinder(unittest.TestCase):
    @parameterized.expand([
        ["dolphins", "dolphins", 5, [
            [1, 5, 6, 7, 9, 13, 17, 19, 22, 25, 26, 27, 31, 32, 39, 41, 48, 54, 56, 57, 60],
            [3, 8, 12, 14, 16, 20, 33, 34, 36, 37, 38, 40, 43, 44, 46, 49, 50, 52, 58, 59],
            [35, 4, 11, 45, 15, 18, 51, 23, 21, 55, 24, 29],
            [0, 2, 10, 42, 47, 28, 30],
            [61, 53]
        ]],
        ["karate", "karate", 3, [
            [32, 33, 34, 3, 9, 15, 16, 19, 21, 23, 24, 25, 26, 27, 28, 29, 30, 31],
            [1, 2, 4, 5, 6, 7, 8, 11, 12, 13, 14, 17, 18, 20, 22],
            [10]
        ]],
        ["krebs", "krebs", 1, [
            [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
             29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
             56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82,
             83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104]

        ]],
        ["football", "football", 2, [
            [1, 12, 14, 17, 18, 19, 20, 25, 26, 27, 29, 30, 31, 33, 34, 35, 36, 37, 38, 42, 43, 44, 45, 48, 54, 55, 56,
             57, 58, 59, 61, 62, 63, 65, 66, 70, 71, 75, 76, 79, 80, 85, 86, 87, 89, 91, 92, 94, 95, 96, 97, 99, 101,
             103, 105, 109, 112, 113],
            [0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 16, 21, 22, 23, 24, 28, 32, 39, 40, 41, 46, 47, 49, 50, 51,
             52, 53, 60, 64, 67, 68, 69, 72, 73, 74, 77, 78, 81, 82, 83, 84, 88, 90, 93, 98, 100, 102, 104, 106,
             107, 108, 110, 111, 114]
        ]]
    ])
    def test_find_communities(self, dirname, filename, number_of_communities, expected):
        os.chdir("{}/setup/real/{}".format(ROOT_DIR, dirname))
        graph = DataHandler.read_data(filename, log_progress=False)
        communities_own = CommunityFinder.find_communities(graph, number_of_communities, log_progress=False)
        self.assertEqual(sorted(expected, key=len), sorted(communities_own, key=len))
