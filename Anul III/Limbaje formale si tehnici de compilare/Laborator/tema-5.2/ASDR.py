class ASDR:
    def __init__(self, grammar):
        self.grammar = grammar

    @staticmethod
    def show_current_state(current_state, index, working_stack, input_stack):
        if len(working_stack) > 0:
            if len(input_stack) > 0:
                print(f"( {current_state} , {index} , {working_stack} , {input_stack} )")
            else:
                print(f"( {current_state} , {index} , {working_stack} , ϵ )")
        else:
            if len(input_stack) > 0:
                print(f"( {current_state} , {index} , ϵ , {input_stack} )")
            else:
                print(f"( {current_state} , {index} , ϵ , ϵ )")

    def get_production_rule_on_index(self, symbol, index):
        return self.grammar.productions[symbol][index]

    def descent_recursive_parsing(self, input_sequence):
        working_stack = ""
        input_stack = self.grammar.start_symbol
        index = 1
        current_state = 'q'
        self.show_current_state(current_state, index, working_stack, input_stack)

        production_history = []
        prod_index = 0
        last_input_sequence_char = None
        while True:
            if len(input_sequence) == 0 and len(input_stack) > 0:
                input_sequence = last_input_sequence_char
                current_state = 'r'
                self.show_current_state(current_state, index, working_stack, input_stack)
                reset_to_prod = production_history[0]
                production_history = production_history[1:]
                if len(production_history) == 0:
                    self.show_current_state("r", reset_to_prod[0], reset_to_prod[1], reset_to_prod[2])
                    self.show_current_state("e", 1, "", input_stack)
                    return False

                index = reset_to_prod[0]
                working_stack = reset_to_prod[1]
                input_stack = reset_to_prod[2]
                prod_index = reset_to_prod[3]

            if len(input_stack) == 0:
                self.show_current_state('t', index, working_stack, "")
                return True

            curr_symbol = input_stack[0]
            if curr_symbol in self.grammar.neterminali:
                current_state = 'q'
                production_to_expand_to = self.get_production_rule_on_index(curr_symbol, prod_index)
                if prod_index < len(self.grammar.productions[curr_symbol]) - 1:
                    production_history.insert(0, [index, working_stack, input_stack, prod_index + 1])
                input_stack = production_to_expand_to + input_stack[1:] 
                    
                working_stack += str(prod_index + 1)
                self.show_current_state(current_state, index, working_stack, input_stack)
            elif curr_symbol in self.grammar.terminali:
                if input_sequence[0] == input_stack[0]:
                    current_state = 'q'
                    index += 1
                    working_stack += input_stack[0]
                    last_input_sequence_char = input_stack[0]
                    input_stack = input_stack[1:]
                    input_sequence = input_sequence[1:]
                    prod_index = 0
                    self.show_current_state(current_state, index, working_stack, input_stack)
                else:
                    current_state = 'r'
                    self.show_current_state(current_state, index, working_stack, input_stack)
                    reset_to_prod = production_history[0]
                    production_history = production_history[1:]
                    if len(production_history) == 0:
                        self.show_current_state("r", reset_to_prod[0], reset_to_prod[1], reset_to_prod[2])
                        self.show_current_state("e", 1, "", input_stack)
                        return False

                    index = reset_to_prod[0]
                    working_stack = reset_to_prod[1]
                    input_stack = reset_to_prod[2]
                    prod_index = reset_to_prod[3]
                    