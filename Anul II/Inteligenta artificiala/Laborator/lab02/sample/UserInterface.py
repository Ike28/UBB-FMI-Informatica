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
        rel_path_to_res = "/setup/real"

        target_directory = input("directory: ").strip()
        if not os.path.isdir("{}/{}/{}".format(base_directory, rel_path_to_res, target_directory)):
            print("$ '{}/{}' is not a valid relative setup directory path. Aborting."
                  .format(rel_path_to_res, target_directory))
            return None

        target_file = input("gml input filename: ").strip()
        if not os.path.isfile("{}/{}/{}/{}.gml".format(
                base_directory, rel_path_to_res, target_directory, target_file)):
            print("$ '{}.gml' not found in '{}/{}/'. Aborting."
                  .format(target_file, rel_path_to_res, target_directory))
            return None

        input_method = input('method (own/lib): ').strip()
        if input_method != "own" and input_method != "lib":
            print("$ Invalid computation method. Aborting.")
            return None

        os.chdir("{}/{}/{}".format(ROOT_DIR, rel_path_to_res, target_directory))

        input_number_of_communities = int(input('number of communities: ').strip())

        return target_file, input_method, input_number_of_communities
