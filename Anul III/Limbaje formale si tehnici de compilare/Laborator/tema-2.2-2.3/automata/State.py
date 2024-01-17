class State:
    def __init__(self, val):
        self.val = val
        self.links = []

    def add_link(self, link):
        self.links.append(link)

    def __str__(self):
        state = "(%s):\n" % self.val
        for link in self.links:
            state += "\t" + link + "\n"
        return state

    def __add__(self, other):
        return str(self) + other

    def __radd__(self, other):
        return other + str(self)

    def equals(self, state):
        ok = (self.val == state.val)
        if len(self.links) == len(state.links):
            for i in range(len(self.links)):
                ok = ok and (self.links[i] == state.links[i])
            return ok
        else:
            return False
