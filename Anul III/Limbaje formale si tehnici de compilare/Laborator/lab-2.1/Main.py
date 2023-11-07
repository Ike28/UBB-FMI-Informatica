from Parser import Parser
from exception.AutomataNotDeterministicException import AutomataNotDeterministicException

# p = Parser('./data/fis.in')
file_parser = Parser('./data/in_class.in')
automaton = file_parser.automaton_from_file()
print(automaton)
try:
    # print(a.accepts('11111111110'))  # fis.in, True
    # print(a.accepts('101010101'))  # fis.in, False
    print(automaton.accepts('aaaaab'))  # in_class.in, True
    print(automaton.accepts('a'))   # in_class.in, True
    print(automaton.accepts('b'))   # in_class.in, True
    print(automaton.accepts('aaaaabbbbb'))  # in_class.in, True
    print(automaton.accepts('aba'))     # in_class.in, (False, ab)

    state = input('\nState to inspect: ')
    char = input('Alphabet symbol: ')
    print("\nTransition: %s ----%s----> %s" % (state, char, automaton.single_transition(state, char)))
except AutomataNotDeterministicException:
    print('Automaton is non-deterministic!')
    exit(1)
