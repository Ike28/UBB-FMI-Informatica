import re


class Gramatica:
    def __init__(self):
        self.terminali = []
        self.neterminali = []
        self.productions = {}
        self.start_symbol = None
        self.epsilons = []

    @staticmethod
    def is_non_terminal(term):
        regex_id = re.compile(r'[a-z]')
        regex_symbol = re.compile(r'[^a-zA-Z]')
        return regex_id.match(term) or regex_symbol.match(term)

    def add_right_production_members(self, line, line_index):
        if line_index == 0 and self.start_symbol is None:
            self.start_symbol = line.split(' ')[0]

        right_prod_member = line.split(' ')
        
        for lett in right_prod_member[0]:
            if self.is_non_terminal(lett):
                raise Exception(f'Gramatica nu e independenta de context linia {line_index}')
            else:
                if lett not in self.neterminali:
                    self.neterminali.append(lett)

    def add_left_production_members(self, line):
        left_prod_members = line.split(' ')

        if left_prod_members[1] == '$':
            self.epsilons.append(left_prod_members[0])

        for letter in left_prod_members[1]:
            if self.is_non_terminal(letter):
                if letter not in self.terminali:
                    self.terminali.append(letter)
            if letter not in self.neterminali and letter != "$":
                if letter not in self.terminali:
                    self.terminali.append(letter)

    def add_production_rules(self, line):
        line_split = line.split(' ')
        right_member = line_split[0]
        left_member = line_split[1]
        
        if right_member in self.productions.keys():
            self.productions[right_member].append(left_member)
        else:
            self.productions[right_member] = []
            self.productions[right_member].append(left_member)
    