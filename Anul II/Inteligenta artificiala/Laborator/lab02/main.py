from CommunityFinder import *
from DataHandler import *
from UserInterface import *


def main():
    settings = UserInterface.read_configuration()
    if settings is None:
        return

    target_file = settings[0]
    input_method = settings[1]
    input_number_of_communities = settings[2]

    graph = DataHandler.read_data(target_file)
    communities = CommunityFinder.find_communities(graph, input_number_of_communities, input_method)
    graph = DataHandler.read_data(target_file, log_progress=False)
    DataHandler.plot_network(graph, communities)


if __name__ == "__main__":
    main()
