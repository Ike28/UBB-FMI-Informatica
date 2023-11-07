from automata.Automaton import Automaton
from automata.Link import Link
from automata.State import State


class Parser:
    def __init__(self, file_path: str):
        self.__filename = file_path

    def automaton_from_file(self):
        states, alphabet, transition_function, initial_state, terminal_states = self.__parse_file()
        states_names = {}
        for s in states:
            states_names[s] = State(s)

        for from_state in transition_function.keys():
            for t in transition_function[from_state]:
                c, to_state = t[0], t[1]
                states_names[from_state].add_link(Link(states_names[from_state], c, states_names[to_state]))

        states_list = []
        for s in states:
            states_list.append(states_names[s])
        terminal_list = []
        for s in terminal_states:
            terminal_list.append(states_names[s])

        a = Automaton(states_names[initial_state], states_list, terminal_list)
        return a

    @staticmethod
    def __parse_line(line: str):
        elements = [e.replace("'", "") for e in line.split('{')[1].split('}')[0].split(',')]
        return elements

    @staticmethod
    def __parse_transition_function(pairs: list):
        transitions = {}
        for pair in pairs:
            from_state = pair.split('[')[0].replace("'", "")
            transitions[from_state] = []
            for t in pair.split('[')[1].split(']')[0].split(';'):
                c = t.split(':')[0].replace("'", "")
                to_state = t.split(':')[1].replace("'", "")
                transitions[from_state].append((c, to_state))
        return transitions

    def __parse_file(self):
        with open(self.__filename, 'r') as f:
            lines = f.readlines()
        states = self.__parse_line(lines[0])
        alphabet = self.__parse_line(lines[1])
        initial_state = lines[3].split('=')[1].split(',')[0].replace("'", "")
        terminal_states = self.__parse_line(lines[4])
        transition = self.__parse_line(lines[2])
        transition_function = self.__parse_transition_function(transition)
        return states, alphabet, transition_function, initial_state, terminal_states
