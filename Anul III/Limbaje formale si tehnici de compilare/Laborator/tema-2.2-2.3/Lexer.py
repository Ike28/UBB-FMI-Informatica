import re
from collections import defaultdict
from contextlib import suppress

from automata.AutomatonParser import AutomatonParser
from tabela_simboluri.tabela_simboluri import TabelaSimboluri


class Lexer:
    def __init__(self):
        self.__path_atomi = 'config/atomi.in'
        self.__path_fip = 'export/fip.out'
        self.__path_ts_constant = 'export/ts_const.out'
        self.__path_ts_identificator = 'export/ts_ident.out'
        self.__tabela_simboluri_const = TabelaSimboluri()
        self.__tabela_simboluri_ident = TabelaSimboluri()
        self.__fip = list()
        self.__citire_separatori_si_keywords()
        self.__af_identificatori = AutomatonParser('config/af_identificatori.in').automaton_from_file()
        self.__af_numere = AutomatonParser('config/af_numere.in').automaton_from_file()
        self.__af_operatori = AutomatonParser('config/af_operatori.in').automaton_from_file()
        self.__af_string = AutomatonParser('config/af_string.in').automaton_from_file()

    def scan_program(self, path_fisier):
        """
        Scaneaza un program din path-ul dat si cauta erori lexicale. La sfarsit salveaza tabela de simboluri si
        si forma interna a programului in cate un fisier fiecare.
        :param path_fisier: path-ul programului ; string
        :return: fip (list), ts_const, ts_ident (Tabela Simboluri),
                mesaj_iesire ("Corect Lexical" | "Eroare lexicala la linia...")
        """
        linii = self.__citire_linii_fisier(path_fisier)
        mesaj_iesire = "Corect Lexical"
        for numar_linie, linie in linii:
            linie = linie.strip()
            try:
                self.scan_linie(linie)
            except (KeyError, ValueError) as err:
                err_str = str(err).strip("'")
                col_position = err_str.index(':')
                err_str = err_str[:col_position + 1] + "\n" + err_str[col_position + 2:]
                mesaj_iesire = f"Eroare lexicala la linia {numar_linie + 1}: {err_str}"
        self.__scrie_fip_in_fisier()
        self.__scrie_ts_in_fisier(self.__path_ts_constant, self.__tabela_simboluri_const, "Tabela de Constante - "
                                                                                          "reprezentare hash-table")
        self.__scrie_ts_in_fisier(self.__path_ts_identificator, self.__tabela_simboluri_ident, "Tabela de "
                                                                                               "Identificatori - "
                                                                                               "reprezentare "
                                                                                               "hash-table")
        return self.__fip, self.__tabela_simboluri_const, self.__tabela_simboluri_ident, mesaj_iesire

    def scan_linie(self, linie):
        """
        Scaneaza o linie data pentru erori lexicale folosind algoritmul:
            1. Atomizare
            2. Clasificare
            3. Codificare
        Obiectele self.__fip, self.__tabela_simboluri_ident si self.__tabela_simboluri_const vor fi modificate
        la sfarsitul functiei
        :param linie: o linie din program; string
        """
        if self.__e_linie_comentariu(linie):
            return
        atomi = self.atomizare(linie)
        categorie_atomi = self.clasificare(atomi)
        self.codificare(atomi, categorie_atomi)

    def atomizare(self, linie):
        """
        Imparte in atomi o linie din program si returneaza atomii ca lista.
        :param linie: linie de atomizat; string
        :return: atomii de pe linie
        """
        strings, caractere, nici_string_sau_nici_caracter = self.__extragere_strings_si_caractere(linie)
        atomi = strings + caractere
        atomi += self.__split_nici_strings_nici_caracter(nici_string_sau_nici_caracter)
        return atomi

    def clasificare(self, atomi):
        """
        Clasifica atomii dintr-o lista pe:
            cuvinte rezervate, constante, operatori, separatori, identificatori
        :param atomi: lista de atomi
        :return: dictionar de forma tip_categorie->lista_de_atomi
        """
        categorie_atomi = defaultdict(list)
        for atom in atomi:
            if self.__e_cuvant_rezervat(atom):
                categorie_atomi["cuvinte_rezervate"].append(atom)
            elif self.__e_constanta(atom):
                categorie_atomi["constante"].append(atom)
            elif self.__e_operator(atom):
                categorie_atomi["operatori"].append(atom)
            elif self.__e_separator(atom):
                categorie_atomi["separatori"].append(atom)
            elif self.__e_identificator(atom):
                categorie_atomi["identificatori"].append(atom)
            else:
                raise ValueError(f"Atom incorect: {atom}")
        return categorie_atomi

    def codificare(self, atomi, categorie_atomi):
        """
        Adauga o lista de atomi la Tabelele de simboluri sau la FIP dupa categorii
        :param atomi: lista de atomi de adaugat
        :param categorie_atomi: dictionar care are toti atomii clasificati dupa categorie (output de la clasificare)
        """
        # adauga identificatorii si constantele la tabelele de simboluri
        for element in categorie_atomi["identificatori"]:
            with suppress(ValueError):
                self.__tabela_simboluri_ident.add_element(element)
        for element in categorie_atomi["constante"]:
            with suppress(ValueError):
                self.__tabela_simboluri_const.add_element(element)

        # adauga toti (posibilii) atomi in FIP
        for atom in atomi:
            pereche_pozitie = self.__tabela_simboluri_ident.gaseste_pozitie_simbol(atom)
            if pereche_pozitie[1] == -1:
                pereche_pozitie = self.__tabela_simboluri_const.gaseste_pozitie_simbol(atom)
                if pereche_pozitie[1] == -1:
                    self.__fip.append((atom, (-1, -1)))
                else:
                    self.__fip.append(("'const'", pereche_pozitie))
            elif self.__e_identificator(atom):
                self.__fip.append(("'id'", pereche_pozitie))

    def __scrie_fip_in_fisier(self):
        with open(self.__path_fip, 'w') as f:
            f.write("Forma Interna a Programului - Lista de reprezentare a tuplurilor\n")
            for fip_element in self.__fip:
                f.write(fip_element[0] + " ---> " + str(fip_element[1]) + "\n")

    @staticmethod
    def __scrie_ts_in_fisier(path_ts, tabela: TabelaSimboluri, header: str):
        with open(path_ts, 'w') as f:
            f.write(header)
            f.write(str(tabela))

    def __e_identificator(self, cuvant):
        """
        Verifica daca un cuvant e identificator (utilizand regulile definite in program)
        """
        if len(cuvant) < 256:
            return self.__af_identificatori.accepts(cuvant)
        else:
            return None

    def __e_constanta_numar(self, cuvant):
        """
        Verifica daca un cuvant e constanta (intreaga, reala sau hexa)
        """
        return self.__af_numere.accepts(cuvant)

    def __e_constanta_string(self, cuvant):
        """
        Verifica daca un cuvant e constanta string
        """
        return self.__af_string.accepts(cuvant)

    def __e_constanta(self, cuvant):
        """
        Verifica daca un cuvant e constanta (intreaga, caracter sau string)
        """
        return self.__e_constanta_numar(cuvant) \
            or self.__e_constanta_string(cuvant)

    @staticmethod
    def __e_linie_comentariu(linie):
        """
        Verifica daca o linie este linie comentariu
        """
        regex_pattern = r"^'.*$"
        return re.match(regex_pattern, linie)

    def __e_operator(self, cuvant):
        """
        Verifica daca un cuvant e operator.
        """
        return self.__af_operatori.accepts(cuvant)

    def __e_separator(self, cuvant):
        """
        Verifica daca un cuvant e separator.
        """
        return cuvant in self.__separatori

    def __e_cuvant_rezervat(self, cuvant):
        """
        Verifica daca un cuvant e cuvant rezervat.
        """
        return cuvant in self.__cuvinte_rezervate

    def __extragere_strings_si_caractere(self, linie):
        """
        Ia un string (linie din program) ca input si extrage toate partile care sunt intre ghilimele sau apostrofuri.
        :param linie: linie din program; string
        :return: constante string, constante caracter, si restul componentelor
        examplu:
            input: write("Hey, ce faci?")
            output: constante_string = ["Hey, ce faci?"]
                    constante_caracter = []
                    nici_string_nici_caracter = ["write(", ")"]
        """
        delim_string_grupat = self.__ghilimele_grup(linie, '"')
        delim_caracter_grupat = self.__ghilimele_grup(linie, "'")
        delimitatori = sorted(delim_string_grupat + delim_caracter_grupat, key=lambda x: x[0])
        constante_string = self.__subsecv_string_indecsi(linie, delim_string_grupat)
        constante_caracter = self.__subsecv_string_indecsi(linie, delim_string_grupat)
        nici_string_nici_caracter = \
            self.__subsecv_string_inafara_indecsi(linie, delimitatori) if len(delimitatori) else [linie]
        return constante_string, constante_caracter, nici_string_nici_caracter

    def __split_nici_strings_nici_caracter(self, lista_nici_strings_nici_caractere):
        """
        Ia o lista de componente dintr-o linie cod care nu sunt/contin constante string sau caracter si le atomizeaza
        :param lista_nici_strings_nici_caractere: lista de componente;
        :return: lista continand atomii identificati
        examplu1: input: ["if (c<min) {"]
                  output: ["if", "(", "c", "<", "min", ")", "{"]
        examplu2: input: ["write(", ")"]
                  output: ["write", "(", ")"]
        """
        numere_si_non_constante = []
        for portiune_linie in lista_nici_strings_nici_caractere:
            if portiune_linie == "END IF":
                numere_si_non_constante.append(portiune_linie)
                continue
            splitter = self.__get_regex_splitter()
            portiune_linie = re.split(splitter, portiune_linie)
            portiune_linie = [t for t in portiune_linie if t is not None and t != ' ' and t != '']
            numere_si_non_constante.extend(portiune_linie)
        return self.__reconstruire_numere_cu_semn(numere_si_non_constante)

    def __reconstruire_numere_cu_semn(self, lista_atomi):
        """
        Reconstruieste numere cu semn in cazul in care '+' si '-' sunt folositi ca operatori unari
        :param lista_atomi: lista de atomi
        :return: noua lista de atomi, cu numere cu semn daca exista
        exemple: int a = -2;   aici semnul '-' va fi concatenat cu 2
                 int a = 3-2;     aici semnul minus e de sine statator
        """
        if len(lista_atomi) < 3:
            return lista_atomi
        lista_atomi_noua = [lista_atomi[0]]
        idx = 1
        while idx < len(lista_atomi) - 1:
            prev_elem, element, next_elem = lista_atomi[idx - 1], lista_atomi[idx], lista_atomi[idx + 1]
            e_int_sau_id_prev = self.__e_constanta_numar(prev_elem) or self.__e_identificator(prev_elem)
            e_int_sau_id_next = self.__e_constanta_numar(next_elem) or self.__e_identificator(next_elem)
            if element in ['+', '-'] and not e_int_sau_id_prev and e_int_sau_id_next:
                # operator unar
                lista_atomi_noua.append(element + next_elem)
                idx += 1
            else:
                # operator binar
                lista_atomi_noua.append(element)
            idx += 1
        e_int_sau_id_stl = self.__e_constanta_numar(lista_atomi[-3]) or self.__e_identificator(lista_atomi[-3])
        e_int_sau_id_last = self.__e_constanta_numar(lista_atomi[-1]) or self.__e_identificator(lista_atomi[-1])
        if not (lista_atomi[-2] in ['+', '-'] and not e_int_sau_id_stl and e_int_sau_id_last):
            # operator binar => adauga si ultimul element
            lista_atomi_noua.append(lista_atomi[-1])
        return lista_atomi_noua

    def __ghilimele_grup(self, linie, tip_delim):
        """
        Grupeaza aparitiile de delimitatori pentru constante string/char in perechi
        :param linie: linia cod in care se cauta; string
        :param tip_delim: tipul de caracter delimitator; " sau '
        :return: lista de perechi de delimitatori, ca lista de perechi de indici
        exemplu: input: linie = write("Hey, ce mai faci" + '?' + "???");
                        tip_delim = "
                 output: [(6,23),(33,37)]
        """
        apostrof_index = self.__gaseste_indexul_caracterului(linie, tip_delim)
        num_apostrof = len(apostrof_index)
        if num_apostrof % 2 == 1:
            descriere_apostrof = "ghilimele" if tip_delim == '"' else "apostrof"
            raise KeyError(f"Lipsesc {descriere_apostrof}  in linia urmatoare: {linie}")
        return [(apostrof_index[i], apostrof_index[j])
                for i, j in zip(range(0,  num_apostrof, 2), range(1,  num_apostrof, 2))]

    def __get_regex_splitter(self):
        """
        Construieste un pattern regex utilizat sa atomizeze o linie cod la granularitate maxima cu toti operatorii
        si separatorii.
        :return: pattern regex, string
        """
        splitter_string = r"(\s+)|"
        caractere_speciale = ['*', '+', '(', ')', '[', ']', '^', '$', '+=', '*=', '^=', '\'']
        for splitter_caracter in self.__separatori:
            if splitter_caracter in caractere_speciale:
                splitter_string += '(' + f"\\{splitter_caracter}" + ')' + '|'
            elif splitter_caracter == 'OR':
                splitter_string += '([^FX]' + splitter_caracter + ')' + '|'
            else:
                splitter_string += '(' + splitter_caracter + ')' + '|'
        return splitter_string[:-1]

    def __citire_separatori_si_keywords(self):
        """
        Citeste separatorii si cuvintele rezervate din atomi.in
        """
        linii = self.__citire_linii_fisier(self.__path_atomi)
        for linie_num, linie in linii:
            split_linie = linie.split(':', 1)
            if not len(split_linie):
                continue
            tip_simboluri = split_linie[0]
            simboluri = split_linie[1].split('|')
            if tip_simboluri == 'separatori':
                self.__separatori = simboluri
            elif tip_simboluri == 'cuvinte_rezervate':
                self.__cuvinte_rezervate = simboluri

    @staticmethod
    def __citire_linii_fisier(path_fisier):
        """
        Citeste un fișier și returneaza o lista de perechi (numar_linie_cod, linie_cod), numar_linie_cod>=0
        :param path_fisier: path-ul fisierului; string
        :return: lista de perechi
        """
        with open(path_fisier, 'r') as f:
            linii = f.readlines()
        linii = [(numar_linie, linie.rstrip()) for numar_linie, linie in enumerate(linii)]
        return linii

    @staticmethod
    def __gaseste_indexul_caracterului(string, caracter):
        """
        Returneaza o lista cu indecsii aparitiilor unui caracter intr-un string
        """
        return [idx for idx, ltr in enumerate(string) if ltr == caracter]

    @staticmethod
    def __subsecv_string_indecsi(string, perechi_indecsi):
        """
        Extrage o lista de subsecvente dintr-un string pe baza unor perechi de indecsi
        :param string: un string
        :param perechi_indecsi: lista de perechi de indecsi
        :return: lista de substringuri
        exemplu: input:  string = This is some string to be split
                         perechi_indecsi = [(0, 3), (5, 7), (13, 17)]
                 output: ["This", "is ", "strin"]
        """
        return [string[start: end + 1] for start, end in perechi_indecsi]

    @staticmethod
    def __subsecv_string_inafara_indecsi(string, indecsi):
        """
        Operatia complementara a __subsecv_string_indecsi
        Extrage lista de subsecvente dintr-un string neincluse in perechile de indecsi
        :param string: un string
        :param indecsi: lista de perechi de indecsi
        :return: lista de subsecvente
        exemplu: input:  string = This is some string to be split
                         indecsi = [(0, 3), (5, 7), (13, 17)]
                 output: [" ", "some ", "g to be split"]
        """
        if not len(indecsi):
            return []
        strings = [string[:indecsi[0][0]]]
        start = indecsi[0][1]
        for index_pair in indecsi[1:]:
            end = index_pair[0]
            strings.append(string[start + 1: end])
            start = index_pair[1]
        strings.append(string[indecsi[-1][1] + 1:])
        return [s for s in strings if len(s) > 0]
