import networkx as nx
import matplotlib.pyplot as plt
import numpy as np


class DataHandler:
    @staticmethod
    def __get_colors(communities_list):
        """
        Calculates node_color param for matplotlib.pyplot.draw_networkx_nodes() based on a list of communities
        :param communities_list: contains communities as lists of nodes
        :return: list
        """
        colors_for_nodes = {}
        index = 0
        for community in communities_list:
            index += 1
            for node in community:
                colors_for_nodes[node] = index

        result = []
        for node in sorted(colors_for_nodes.keys()):
            result.append(colors_for_nodes[node])
        return result

    @staticmethod
    def plot_network(graph, communities):
        """
        Plots a network visually
        :param graph: NetworkX graph containing the network
        :param communities: contains communities as lists of nodes
        """
        print("\nPlotting network... ", end="")
        colors = DataHandler.__get_colors(communities)
        np.random.seed(123)
        pos = nx.spring_layout(graph)
        plt.figure(figsize=(6, 6))
        if colors is not None:
            nx.draw_networkx_nodes(graph, pos, node_size=100, cmap=plt.cm.RdYlBu, node_color=colors)
        else:
            nx.draw_networkx_nodes(graph, pos, node_size=100, cmap=plt.cm.RdYlBu)
        nx.draw_networkx_edges(graph, pos, alpha=0.3)
        plt.show()
        print(u'Done \u2713')

    @staticmethod
    def read_data(target_file, log_progress=True):
        """
        Reads a graph from an existing .gml file in the current working directory
        :param target_file: filename of input .gml data
        :param log_progress: False will cancel all console messages
        :return: NetworkX graph
        """
        if log_progress:
            print("\nReading data... ", end="")
        graph = nx.read_gml("{}.gml".format(target_file), label='id')
        if log_progress:
            print(u'Done \u2713')
            print("     input: {} nodes, {} edges".format(graph.number_of_nodes(), graph.number_of_edges()))
        return graph
