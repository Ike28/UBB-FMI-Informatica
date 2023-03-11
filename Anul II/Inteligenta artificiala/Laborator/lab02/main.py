import itertools
import numpy as np
import networkx as nx
import matplotlib.pyplot as plt
from networkx.algorithms.community.centrality import girvan_newman
import os


def plot_network(graph, colors=None):
    print("\nPlotting network... ", end="")
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


def edge_to_remove(graph):
    edges = nx.edge_betweenness_centrality(graph)
    edges_betweenness_list = list(edges.items())
    edges_betweenness_list.sort(key=lambda x: x[1], reverse=True)  # sort based on betweenness value

    # return the edge in the form (a,b)
    return edges_betweenness_list[0][0]


def girvan_newman_algorithm(graph, max_number_of_communities=2):
    print("Running algorithm... ", end="")

    connected_components = nx.connected_components(graph)
    nr_components = nx.number_connected_components(graph)
    while nr_components < max_number_of_communities:
        edge = edge_to_remove(graph)
        graph.remove_edge(edge[0], edge[1])
        connected_components = nx.connected_components(graph)
        nr_components = nx.number_connected_components(graph)
    print(u'Done \u2713')
    return connected_components


def get_communities_nodes_values(communities):
    print("Processing communities...", end="")
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
    print(u'Done \u2713')
    return result


def get_colors(communities_list):
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


def read_configuration():
    base_directory = os.path.dirname(os.path.realpath(__file__))

    target_directory = input("directory: ").strip()
    if not os.path.isdir("{}/real/{}".format(base_directory, target_directory)):
        print("$ './real/{}' is not a valid relative directory path.".format(target_directory))
        return None

    target_file = input("gml input filename: ").strip()
    if not os.path.isfile("{}/real/{}/{}.gml".format(base_directory, target_directory, target_file)):
        print("$ '{}.gml' not found in './real/{}/'.".format(target_file, target_directory))
        return None

    input_method = input('method (own/lib): ').strip()

    os.chdir("real/{}".format(target_directory))

    input_number_of_communities = int(input('number of communities: ').strip())

    return target_file, input_method, input_number_of_communities


def main():
    settings = read_configuration()
    if settings is None:
        return

    target_file = settings[0]
    input_method = settings[1]
    input_number_of_communities = settings[2]

    print("Reading data... ", end="")
    graph = nx.read_gml("{}.gml".format(target_file), label='id')
    print(u'Done \u2713')
    print("     input: {} nodes, {} edges".format(graph.number_of_nodes(), graph.number_of_edges()))

    if input_method == 'own':
        processed = girvan_newman_algorithm(graph, max_number_of_communities=input_number_of_communities)
        communities = get_communities_nodes_values(processed)

    elif input_method == 'lib':
        print("Running algorithm... ", end="")
        processed = girvan_newman(graph)
        print(u'Done \u2713')
        limited_result = itertools.takewhile(lambda c: len(c) <= 2, processed)
        communities = []
        print("\nProcessing communities...", end="")
        for instance in limited_result:
            communities = list(c for c in instance)
        print(u'Done \u2713')

    else:
        print("$ Invalid computation method. Aborting.")
        return

    colors = get_colors(communities)
    print("{} communities found:".format(len(communities)))
    for com in communities:
        print(com)

    original = nx.read_gml("{}.gml".format(target_file), label='id')
    plot_network(original, colors)
    nx.barbell_graph(30, 40)


main()
