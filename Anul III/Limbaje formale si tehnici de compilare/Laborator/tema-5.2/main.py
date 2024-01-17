from Gramatica import Gramatica
from ASDR import ASDR


def create_grammar(productions_file):
    f = open(productions_file, "r")

    gram = Gramatica()

    idx = 0
    for line in f:
        try:
            gram.add_right_production_members(line.rstrip('\n'), idx)
            gram.add_production_rules(line.rstrip('\n'))
        except Exception:
            raise
            
        idx += 1

    f.close()

    f = open(productions_file, "r")
    for line in f:
        gram.add_left_production_members(line.rstrip('\n'))
        
    f.close()

    return gram


def analyze_input_file(dr):
    f = open("input/input.txt", "r")

    for input_sequence in f:
        input_sequence = input_sequence.rstrip('\n')
        if dr.descent_recursive_parsing(input_sequence):
            print()
            print(f"{input_sequence} ∈ L(G)")
            print()    
        else:
            print()
            print(f"{input_sequence} ∉ L(G)")
            print()    

    f.close()


def main():
    try:
        gram = create_grammar("gram.txt")
    except Exception as e:
        print("Error " + str(e))
        return

    print(gram.neterminali)

    dr = ASDR(gram)

    analyze_input_file(dr)


if __name__ == '__main__':
    main()
