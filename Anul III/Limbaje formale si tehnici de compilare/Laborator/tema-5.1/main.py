
from gramatica import Gramatica


def main():
    gramatica_path = 'utils/gram'
    with open(gramatica_path, 'r') as gf:
        gramatica = gf.readline().rstrip()
    g = Gramatica(gramatica)
    print(gramatica)

    g.print_elem_gramaticii()

    e_regular = g.este_regulara()
    print("\nGramatica regulara: %s\n" % e_regular)
    g.print_right_recursive_productions()


if __name__ == "__main__":
    main()
