import os
from definitions import ROOT_DIR


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

        input_method = input('method (own - proprietary algorithm ; gn - girvan-newman ; lv - louvain)\n: ').strip()
        if input_method != "own" and input_method != "gn" and input_method != "lv":
            print("$ Invalid computation method. Aborting.")
            return None

        os.chdir("{}/{}/{}".format(ROOT_DIR, rel_path_to_res, target_directory))

        input_number_of_communities = None
        if input_method == "own" or input_method == "gn":
            input_number_of_communities = int(input('number of communities: ').strip())

        return target_file, input_method, input_number_of_communities, file_type
