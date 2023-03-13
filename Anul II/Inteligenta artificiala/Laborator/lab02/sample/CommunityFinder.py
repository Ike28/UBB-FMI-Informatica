import itertools
import networkx as nx
from networkx.algorithms.community import girvan_newman, louvain_communities


class CommunityFinder:
    @staticmethod
    def __edge_to_remove(graph):
        """
        Identifies next edge to remove from graph
        :param graph: NetworkX graph
        :return: resulting edge as (starting_node_value, ending_node_value)
        """
        edges = nx.edge_betweenness_centrality(graph)
        edges_betweenness_list = list(edges.items())
        edges_betweenness_list.sort(key=lambda x: x[1], reverse=True)

        return edges_betweenness_list[0][0]

    @staticmethod
    def __girvan_newman_algorithm(graph, max_number_of_communities=2):
        """
        Identifies a given number of communities in a graph
        :param graph: NetworkX graph
        :param max_number_of_communities: number of communities to identify
        :return: generator for communities as sets of node values
        """

        connected_components = nx.connected_components(graph)
        nr_components = nx.number_connected_components(graph)
        while nr_components < max_number_of_communities:
            edge = CommunityFinder.__edge_to_remove(graph)
            graph.remove_edge(edge[0], edge[1])
            connected_components = nx.connected_components(graph)
            nr_components = nx.number_connected_components(graph)
        return connected_components

    @staticmethod
    def __get_communities_as_lists(communities):
        """
        Generates representation of found communities as list of node values
        :param communities: generator for community sets
        :return: list of lists
        """
        communities_sorted = []
        c = next(communities, None)
        while c is not None:
            communities_sorted.append(c)
            c = next(communities, None)
        communities_sorted = sorted(communities_sorted, key=len, reverse=True)

        result = []
        for community in communities_sorted:
            current = []
            for node in community:
                current.append(node)
            result.append(current)
        return result

    @staticmethod
    def __handle_own_processing(graph, input_number_of_communities, log_progress=True):
        processed = CommunityFinder.__girvan_newman_algorithm(graph,
                                                              max_number_of_communities=input_number_of_communities)
        if log_progress:
            print(u'Done \u2713')
            print("Processing communities...", end="")
        communities = CommunityFinder.__get_communities_as_lists(processed)
        if log_progress:
            print(u'Done \u2713')
        return communities

    @staticmethod
    def __handle_newman_processing(graph, input_number_of_communities, log_progress=True):
        processed = girvan_newman(graph)
        if log_progress:
            print(u'Done \u2713')
            print("Processing communities...", end="")
        limited_result = itertools.takewhile(lambda c: len(c) <= input_number_of_communities, processed)
        communities = []
        for instance in limited_result:
            communities = list(list(c) for c in instance)
        if log_progress:
            print(u'Done \u2713')
        return communities

    @staticmethod
    def __handle_louvain_processing(graph, log_progress=True):
        processed = louvain_communities(graph, resolution=0.7)
        if log_progress:
            print(u'Done \u2713')
            print("Processing communities...", end="")
        communities = list(list(c) for c in processed)
        print(u'Done \u2713')
        return communities

    @staticmethod
    def find_communities(graph, input_number_of_communities=None, input_method="own", log_progress=True):
        """
        Finds communities in a graph
        :param graph: NetworkX graph
        :param input_number_of_communities: specifiable for "own" and "grv" methods, int
        :param input_method: 'own' - proprietary algorithm / 'lib' - NetworkX algorithms
        :param log_progress: False will cancel all console messages
        :return:
        """
        if log_progress:
            print("Running algorithm... ", end="")
        if input_method == 'own':
            communities = CommunityFinder.__handle_own_processing(graph, input_number_of_communities, log_progress)
        elif input_method == 'lv':
            communities = CommunityFinder.__handle_louvain_processing(graph, log_progress)
        else:
            communities = CommunityFinder.__handle_newman_processing(graph, input_number_of_communities, log_progress)

        return communities
