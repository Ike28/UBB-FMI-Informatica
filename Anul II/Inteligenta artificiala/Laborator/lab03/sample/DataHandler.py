import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
from numpy.random.mtrand import randint


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
    def plot_network(graph, communities=None):
        """
        Plots a network visually
        :param graph: NetworkX graph containing the network
        :param communities: contains communities as lists of nodes
        """
        print("\nPlotting network... ")
        np.random.seed(123)
        pos = nx.spring_layout(graph)
        plt.figure(figsize=(6, 6))
        if communities is not None:
            print("     coloring communities... ", end="")
            colors = DataHandler.__get_colors(communities)
            print(u'Done \u2713')
            nx.draw_networkx_nodes(graph, pos, node_size=100, cmap=plt.cm.RdYlBu, node_color=colors)
        else:
            nx.draw_networkx_nodes(graph, pos, node_size=100, cmap=plt.cm.RdYlBu)
        nx.draw_networkx_edges(graph, pos, alpha=0.3)
        plt.show()
        print(u'Done \u2713')

    @staticmethod
    def read_data(target_file, log_progress=True, file_type="gml"):
        """
        Reads a graph from an existing .gml file in the current working directory
        :param file_type: file type of target file
        :param target_file: filename of input .gml data
        :param log_progress: False will cancel all console messages
        :return: NetworkX graph
        """
        if log_progress:
            print("\nReading data... ", end="")
        if file_type == "gml":
            graph = nx.read_gml("{}.gml".format(target_file), label='id', )
        elif file_type == "gexf":
            graph = nx.read_gexf("{}.gexf".format(target_file))
        elif file_type == "graphml":
            graph = nx.read_graphml("{}.graphml".format(target_file))
        elif file_type == "net":
            graph = nx.read_pajek("{}.net".format(target_file))
        if log_progress:
            print(u'Done \u2713')
            print("     input: {} nodes, {} edges".format(graph.number_of_nodes(), graph.number_of_edges()))

        matrix = nx.to_numpy_matrix(graph)
        degrees = []
        for u in graph:
            d = 0
            for v in graph:
                if matrix.item((u, v)) == 1:
                    d += 1
            degrees.append(d)
        return graph, degrees

    @staticmethod
    def generate_value(low, high):
        return randint(low, high)

    @staticmethod
    def modularity(communities, graph, degrees):
        nodes = graph.number_of_nodes()
        matrix = nx.to_numpy_matrix(graph)
        edges = graph.number_of_edges()
        M = 2 * edges
        Q = 0.0
        for i in range(0, nodes):
            for j in range(0, nodes):
                if communities[i] == communities[j]:
                    Q += (matrix.item((i, j)) - degrees[i] * degrees[j] / M)
        return Q * (1 / M)
