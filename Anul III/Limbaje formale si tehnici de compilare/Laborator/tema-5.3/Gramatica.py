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
        regex_non_terminal = re.compile(r'<[a-zA-Z_]+>')
        return regex_non_terminal.match(term)

    def add_right_production_members(self, line, line_index):
        if line_index == 0 and self.start_symbol == None:
            self.start_symbol = line.split(' ')[0]

        right_prod_member = line.split(' ')

        if self.is_non_terminal(right_prod_member[0]) and (right_prod_member[0] not in self.neterminali):
            self.neterminali.append(right_prod_member[0])

    def add_left_production_members(self, line):
        left_prod_members = line.split(' ')

        if left_prod_members[1] == '$':
            self.epsilons.append(left_prod_members[0])

        for i in range (1, len(left_prod_members)):
            if not self.is_non_terminal(left_prod_members[i]) and (left_prod_members[i] not in self.terminali):
                self.terminali.append(left_prod_members[i])

    def add_production_rules(self, line):
        line_split = line.split(' ')
        right_member = line_split[0]
        left_member = []
        for i in range (1, len(line_split)): 
            left_member.append(line_split[i])
        
        if right_member in self.productions.keys():
            self.productions[right_member].append(left_member)
        else:
            self.productions[right_member] = []
            self.productions[right_member].append(left_member)
    