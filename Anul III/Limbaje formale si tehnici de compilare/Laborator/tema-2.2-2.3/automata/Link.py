class Link:
    def __init__(self, from_state, etiquette, to_state):
        self.from_state = from_state
        self.etiquette = etiquette
        self.to_state = to_state

    def __str__(self):
        return "(%s --%s--> %s)" % (self.from_state.val, self.etiquette, self.to_state.val)

    def __add__(self, other):
        return str(self) + other

    def __radd__(self, other):
        return other + str(self)

    def equals(self, link):
        return (self.from_state == link.from_state) \
            and (self.etiquette == link.etiquette) \
            and (self.to_state == link.to_state)
