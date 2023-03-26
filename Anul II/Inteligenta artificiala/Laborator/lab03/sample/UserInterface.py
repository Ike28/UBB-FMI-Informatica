import os
from definitions import ROOT_DIR
from sample.DataHandler import DataHandler


class UserInterface:
    @staticmethod
    def read_configuration():
        """
        Reads runtime settings from user input and sets current working directory accordingly
        :return: target_file: filename of input data, str
                input_method: "own"/"lib"
                input_number_of_communities: number of communities to find, int
        :return: None in case of bad input
        """
        base_directory = ROOT_DIR
        rel_path_to_res = "/setup"
        file_types = ["gml", "gexf", "graphml", "net"]

        target_directory = input("directory: ").strip()
        if not os.path.isdir("{}/{}/{}".format(base_directory, rel_path_to_res, target_directory)):
            print("$ '{}/{}' is not a valid relative setup directory path. Aborting."
                  .format(rel_path_to_res, target_directory))
            return None

        file_type = input("file type ({}): ".format("".join(e + "/" for e in file_types)[:-1])).strip()
        if file_type not in file_types:
            print("$ '{}' is not an accepted file type. Aborting.".format(file_type))
            return None

        target_file = input("input filename: ").strip()
        if not os.path.isfile("{}/{}/{}/{}.{}".format(
                base_directory, rel_path_to_res, target_directory, target_file, file_type)):
            print("$ '{}.{}' not found in '{}/{}/'. Aborting."
                  .format(target_file, file_type, rel_path_to_res, target_directory))
            return None

        os.chdir("{}/{}/{}".format(ROOT_DIR, rel_path_to_res, target_directory))

        return target_file, file_type

    @staticmethod
    def read_ga_params(graph, degrees):
        generation_strategies = ["standard", "steady-state", "elitism"]
        ga_params = {'population_size': 20, 'generations': 50, 'strategy': "standard"}
        chromosome_params = {'min': 0, 'max': graph.number_of_nodes(), 'function': DataHandler.modularity,
                             'nodes': graph.number_of_nodes(), 'network': graph, 'degrees': degrees}

        input_population_size = input("population size (leave empty for "
                                      + ga_params['population_size'].__str__() + "): ").strip()
        if input_population_size != "":
            ga_params['population_size'] = int(input_population_size)

        input_generations = input("number of generations (leave empty for "
                                  + ga_params['generations'].__str__() + "): ").strip()
        if input_generations != "":
            ga_params['generations'] = int(input_generations)

        function = input("function (leave empty for modularity): ").strip()
        if function != "":
            chromosome_params['function'] = function

        input_strategy = input("generation strategy ({}): ".format("".join(e + "/" for e in
                                                                           generation_strategies)[:-1])).strip()
        if input_strategy not in generation_strategies:
            print("$ '{}' is not an accepted generation strategy. Aborting.".format(input_strategy))
            return None
        ga_params['strategy'] = input_strategy

        return ga_params, chromosome_params

