import re


class Gramatica:
    def __init__(self, gramatica_string):
        self.regex = self.do_regex(gramatica_string)
        self.simbolDeStart = self.set_simbol_de_start()
        self.terminale = self.set_simboluri(self.regex.group(4))
        self.nonTerminale = self.set_simboluri(self.regex.group(2))
        self.productii = self.set_productii(self.regex.group(7))

    def este_regulara(self):
        productie_pattern = r"^[a-z]+[a-zA-Z]*$"
        eps_pattern = r"^&$"
        eps = False
        for p in self.productii:
            if re.match(eps_pattern, p[1]):
                eps = True
                if p[0] != self.simbolDeStart:
                    return False

        for p in self.productii:
            if not re.match(productie_pattern, p[1]) and not re.match(eps_pattern, p[1]) \
                    or (eps and self.simbolDeStart in p[1]):
                return False
        return True

    def print_right_recursive_productions(self):
        print('Productii recursive la dreapta:')
        for p in self.productii:
            non_terminal_regex = r"^[a-zA-Z]*?" + re.escape(p[0]) + "$"
            if re.match(non_terminal_regex, p[1]):
                print(p[0] + '->' + p[1])

    @staticmethod
    def do_regex(gramatica_string):
        pattern = r"(G\s*=\s*\()" \
                  r"(?P<non_terminale>\s*{\s*([A-Z]\s*,\s*)*[A-Z]+\s*})\s*,\s*" \
                  r"(?P<terminale>{\s*([a-z0-9]\s*,\s*)*[a-z0-9]+\s*})\s*,\s*" \
                  r"(?P<simbol_de_start>[A-Z]{1})\s*,\s*" \
                  r"(?P<productii>\s*{\s*([A-Z]{1}->(&|[a-z0-9]+[A-Z]?|[A-Z]+[a-z0-9]?|[a-z0-9]+[A-Z]*|[A-Z]{1})" \
                  r"\s*,*\s*)+\s*}\s*)(\))$"
        cauta = re.search(pattern, gramatica_string)
        return cauta

    # Print regex
    def print_regex(self):
        print('Non-terminale : ' + self.regex.group('non_terminale'))
        print('Terminale : ' + self.regex.group('terminale'))
        print('Simbol de start : ' + self.regex.group('simbol_de_start'))
        print('Productii : ' + self.regex.group('productii'))

    # Setters
    def set_simbol_de_start(self):
        return self.regex.group(6)

    @staticmethod
    def set_simboluri(regex):
        return re.sub('{|}| ', '', regex).split(',')

    @staticmethod
    def set_productii(regex):
        return list(map(lambda l: tuple(l), list(map(lambda s: s.split('->'), re.sub('{|}| ', '', regex)
                                                     .split(',')))))

    def get_productii_non_term(self, non_term_dat):
        productii_non_term = []
        for non_terminal, p_dreapta in self.productii:
            if non_terminal == non_term_dat:
                productii_non_term.append((non_terminal, p_dreapta))
        return productii_non_term

    def print_elem_gramaticii(self):
        self.print_regex()
