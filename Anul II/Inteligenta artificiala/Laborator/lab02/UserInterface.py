import os


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
        base_directory = os.path.dirname(os.path.realpath(__file__))

        target_directory = input("directory: ").strip()
        if not os.path.isdir("{}/real/{}".format(base_directory, target_directory)):
            print("$ './real/{}' is not a valid relative directory path. Aborting.".format(target_directory))
            return None

        target_file = input("gml input filename: ").strip()
        if not os.path.isfile("{}/real/{}/{}.gml".format(base_directory, target_directory, target_file)):
            print("$ '{}.gml' not found in './real/{}/'. Aborting.".format(target_file, target_directory))
            return None

        input_method = input('method (own/lib): ').strip()
        if input_method != "own" and input_method != "lib":
            print("$ Invalid computation method. Aborting.")
            return None

        os.chdir("real/{}".format(target_directory))

        input_number_of_communities = int(input('number of communities: ').strip())

        return target_file, input_method, input_number_of_communities
