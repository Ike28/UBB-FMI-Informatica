from exception.AutomataNotDeterministicException import AutomataNotDeterministicException


class Automaton:
    def __init__(self, initial_state, states, terminal_states: list):
        self.initial_state = initial_state
        self.states = states
        self.terminal_states = terminal_states
        self.deterministic = self.__is_deterministic()

    @staticmethod
    def get_next_state(current_node, etiquette):
        for link in current_node.links:
            if link.etiquette == etiquette:
                return link.to_state
        return None

    def single_transition(self, from_state: str, char: str):
        state = [s for s in self.states if s.val == from_state][0]
        next_state = self.get_next_state(state, char)
        return next_state.val

    def accepts(self, string):
        if not self.deterministic:
            raise AutomataNotDeterministicException
        state = self.initial_state
        for i in range(len(string)):
            state = self.get_next_state(state, string[i:][0])
            if state is None:
                if i == 0:
                    return False, None
                return False, string[:i]
        if self.terminal_states.__contains__(state):
            return True
        return False, string[:-1]

    def __is_deterministic(self):
        for state in self.states:
            transitions_alphabet = set()
            for link in state.links:
                if link.etiquette in transitions_alphabet:
                    return False
                transitions_alphabet.add(link.etiquette)
        return True

    def __str__(self):
        terminal_states_str = [s.val for s in self.terminal_states]
        automata = "Initial state: %s\nTerminal states: %s\n" % (self.initial_state.val, terminal_states_str)

        for state in self.states:
            automata += state
        return automata

    def __add__(self, other):
        return str(self) + other

    def __radd__(self, other):
        return other + str(self)
