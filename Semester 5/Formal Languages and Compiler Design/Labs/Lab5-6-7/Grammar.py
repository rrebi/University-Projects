class Grammar:
    def __init__(self):
        self.N = []  # non-terminals
        self.E = []  # terminals
        self.S = ""  # starting symbol
        self.P = {}  # finite set of productions. keys=nonterminals, values=lists of production rules

    def rebuild(self):
        self.N = []
        self.E = []
        self.S = ""
        self.P = {}

    @staticmethod
    def __process_line(line: str, delimiter=' '):
        # removes whitespaces and {} and adds delimiter
        elements = line.strip().strip('{}').split(delimiter)
        if len(elements) > 1:
            elements[0] += delimiter
            elements[0:2] = [''.join(elements[0:2])]

        # only nonempty elems
        return [element.strip() for element in elements if element]

    def read_from_file(self, file_name: str):
        self.rebuild()  # clears existing grammar attributes (n,e,s,p)
        with open(file_name) as file:
            line = next(file)  # nonterminals
            self.N = self.__process_line(line.split('=')[1], ', ')

            line = next(file)  # terminals
            self.E = self.__process_line(line[line.find('=') + 1:-1].strip(), ', ')

            line = next(file)  # starting symbol
            self.S = self.__process_line(line.split('=')[1], ', ')[0]

            # production rules
            line = file.readline()
            while line.strip() and ' -> ' not in line:  # skip lines until the production rules
                line = file.readline()

            while line:
                if ' -> ' in line:
                    source, productions = line.split(" -> ")  # to extract the source nonterminal and its productions
                    source = source.strip()
                    for production in productions.split('|'):
                        production = production.strip().split()
                        if source in self.P:
                            self.P[source].append(production)  # if it is in P => appends the current production
                        else:
                            self.P[source] = [production]
                line = file.readline()

    def check_cfg(self):
        has_starting_symbol = False
        for key in self.P.keys():  # keys of nonterminals in p
            if key == self.S:
                has_starting_symbol = True
            if key not in self.N[0].split():  # nonterminal in the grammar is present in the set of nonterminals
                return False
        if not has_starting_symbol:
            return False
        for production in self.P.values():  # checks for valid nonterminal or terminal
            for rhs in production:
                for value in rhs:
                    if value not in self.N[0].split() and value not in self.E[0].split():
                        return False
        return True

    def get_non_terminals(self):
        return self.N

    def get_terminals(self):
        return self.E

    def get_start_symbol(self):
        return self.S

    def get_productions(self):
        return self.P

    def get_productions_for_non_terminal(self, nt):
        return self.P.get(nt, [])

    def __str__(self):
        result = "N = " + str(self.N) + "\n"
        result += "E = " + str(self.E) + "\n"
        result += "S = " + str(self.S) + "\n"
        result += "P = " + str(self.P) + "\n"
        return result