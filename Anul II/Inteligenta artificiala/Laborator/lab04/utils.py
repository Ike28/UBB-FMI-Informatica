import random
import xml.etree.ElementTree as ET
import numpy as np
import networkx as nx
from networkx.drawing.tests.test_pylab import plt


def parse_xml(name):
    """
    Method used for parsing an xml file, whose name is given as a parameter.
    :param name: the name of the xml file that needs to be parsed
    :return: the network that was read from the xml file
    """

    file_name = "data/" + name + ".xml"

    tree = ET.parse(file_name)
    root = tree.getroot()
    graph = root.findall("graph")
    vertices = graph[0].findall("vertex")

    net = {"noNodes": len(vertices)}
    net["mat"] = [[0 for _ in range(0, net["noNodes"])] for _ in range(0, net["noNodes"])]
    net["weightSum"] = 0
    net["edgeNum"] = 0

    i = 0
    for vertex in vertices:

        edges = vertex.findall("edge")
        for edge in edges:

            target = int(edge.text)
            weight = float(edge.attrib["cost"])
            net["mat"][i][target] = weight

            net["weightSum"] += weight
            net["edgeNum"] += 1

        i += 1

    net["weightSum"] /= 2
    net["edgeNum"] /= 2
    net["edgeAvg"] = net["weightSum"] / net["edgeNum"]

    return net


def random_perm(lst):
    """
    Method used for returning a random permutation of the given list.
    :param lst: the list for which a random permutation is needed
    :return: a random permutation of the given list

    """
    return random.sample(lst, len(lst))


def calc_fitness(values, network, shortest_path=False, sp_from=None, sp_to=None):
    """
    Method used for calculating the fitness of a chromosome.
    :param values: the value of the chromosome
    :param network: the graph
    :param shortest_path: True - if the algorithm is run in the shortest path mode; False - otherwise
    :return: the fitness of the given chromosome

    """

    weight_sum = 0
    penalty = network["weightSum"]

    if not shortest_path:

        for i in range(1, len(values)):
            weight = network["mat"][values[i - 1]][values[i]]

            if weight != 0:
                weight_sum += weight

            else:
                weight_sum += penalty

        if network["mat"][values[-1]][values[0]] != 0:
            weight_sum += network["mat"][values[-1]][values[0]]

        else:
            weight_sum += penalty

    else:

        from_pos = 0
        to_pos = 1

        for i in range(0, len(values)):
            if values[i] == sp_from:
                from_pos = i

            if values[i] == sp_to:
                to_pos = i

        if to_pos < from_pos:
            from_pos, to_pos = to_pos, from_pos

        for i in range(from_pos + 1, to_pos + 1):
            if network["mat"][values[i - 1]][values[i]] != 0:
                weight_sum += network["mat"][values[i - 1]][values[i]]

            else:
                weight_sum += penalty

    return weight_sum


def plot(name):
    """
    Method used for plotting a graph, whose name is given as a parameter.
    :param name: the name of the graph which will be plotted
    """

    network = parse_xml(name)

    nm = np.matrix(network["mat"])
    print(nm)

    g = nx.from_numpy_matrix(nm)
    print(g)
    labels = nx.get_edge_attributes(g, "weight")

    pos = nx.spring_layout(g)
    plt.figure(figsize=(6, 6))
    nx.draw_networkx_nodes(g, pos, node_size=600, cmap=plt.cm.RdYlBu, label="string")
    nx.draw_networkx_edge_labels(g, pos, edge_labels=labels)
    nx.draw_networkx_edges(g, pos, alpha=0.3)
    nx.draw_networkx_labels(g, pos, font_size=14)
    plt.savefig("data/visual/" + name + ".png")

