from collections import defaultdict

CAP_DEFAULT = 10


class TabelaSimboluri:
    def __init__(self, dim_tabela=CAP_DEFAULT):
        self.__tabela_dispersie = defaultdict(list)
        self.__capacitate = dim_tabela
        self.__dimensiune = 0

    def __str__(self):
        output_string = ""
        for hash_idx, lista_valori in sorted(self.__tabela_dispersie.items()):
            for idx, valoare in enumerate(lista_valori):
                output_string += f"({hash_idx}, {idx}) ---> {valoare}\n"
        return output_string

    def add_element(self, simbol):
        """
        Adauga un simbol nou in tabela de simboluri.
        :param simbol: noul simbol de inserat in tabela de simboluri; numar sau string
        :except ValueError: daca simbol exista deja in tabela
        """
        key, elem_index = self.gaseste_pozitie_simbol(simbol)
        if elem_index != -1:
            raise ValueError("Elementul exista deja in TS!")
        else:
            self.__tabela_dispersie[key].append(simbol)
            self.__dimensiune += 1

    def get_dim(self):
        """
        :return: dimensiunea curenta (numar de simboluri) a TS-ului
        """
        return self.__dimensiune

    def gaseste_pozitie_simbol(self, simbol):
        """
        Gaseste pozitia unui simbol in tabela de simboluri.
        :param simbol: simbolul ce trebuie cautat; numar sau string
        :return: o pereche de forma (pozitia_in_tabela_de_dispersie, pozitia_in_lista_de_coliziuni
        (daca simbolul exista deja) | -1 (daca simbolul nu exista))
        """
        cheie = self.__dispersie(simbol)
        if simbol in self.__tabela_dispersie[cheie]:
            return cheie, self.__tabela_dispersie[cheie].index(simbol)
        else:
            return cheie, -1

    def __dispersie(self, simbol):
        """
        Functia de dispersie: restul impartirii sumei ASCII a caracterelor din simbol la capacitatea tabelei.
        :param simbol: simbolul de dispersat in tabela; numar sau string
        :return: valoarea dispersiei pentru simbolul dat; int
        """
        suma_ascii = sum([ord(c) for c in str(simbol)])
        return suma_ascii % self.__capacitate
