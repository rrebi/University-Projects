import re

from SymbolTables import SymbolTable


class Scanner:

    def __init__(self, filepath):
        self.operators = ["+", "-", "*", "/", "==", "<=", ">=", "!=", "<", ">", "=", "%"]
        self.separators = ["(", ")", "{", "}", ",", ";", ":", " ", "\n", "\""]
        self.reservedWords = ["var", "int", "str", "read", "print", "if", "else", "do", "while"]
        self.intConstantsST = SymbolTable(200)  # Corrected variable name
        self.strConstantsST = SymbolTable(200)  # Corrected variable name
        self.identifiersST = SymbolTable(200)
        self.pifOutput = []

        self.filePath = filepath

    def readFile(self):
        fileContent = ""

        # Open the file for reading
        with open(self.filePath, 'r') as file:
           for line in file:

               # Add file lines to fileContent
               fileContent = fileContent + line.strip() + "\n"

        return fileContent

    def getProgramTokens(self):
        try:
            content = self.readFile()
            # Initialize variables to store tokens
            tokens = []
            local_word = ""
            in_quoted_string = False

            # Process content character by character
            for char in content:
                if in_quoted_string:
                    local_word += char
                    if char == '"':
                        in_quoted_string is False
                elif char not in self.operators and char not in self.separators and char not in self.reservedWords:
                    local_word += char  # If char is not in the operators, separators, or reserved words, we add it to form the word
                else:
                    if local_word:
                        tokens.append(local_word)  # Add the word
                        local_word = ""
                    if char == '"':
                        local_word = '"'
                        in_quoted_string = True
                    elif char.strip() or char in self.operators or char in self.separators or char in self.reservedWords:
                        tokens.append(char)  # Add the separator, even if the word is empty

            # If there's any remaining word after processing the content
            if local_word:
                tokens.append(local_word)
            # Filter out '\n' strings
            #tokens = [token for token in tokens if token != '\n']

            return tokens

        except FileNotFoundError as e:
            print(e)

        return None

    def scan(self):
        tokens = self.getProgramTokens()
        counter = 0
        position_counter = 0  # Initialize the shared position counter
        identifiers = {}  # Dictionary to store identifiers and their indices
        in_quoted_string = False
        for t in tokens:
            token = t
            if token == "\n":
                counter += 1
            elif in_quoted_string:
                if token.endswith('"'):
                    in_quoted_string = False
                position = self.strConstantsST.insert_string(token, token[1:-1])
                self.pifOutput.append(["STRING_CONSTANT", position_counter])
                position_counter += 1  # Increment the shared position counter
            elif token in self.reservedWords:
                # Set the position to -1 for all reserved words
                position = -1
                self.pifOutput.append([token, position])
            elif token in self.operators:
                self.pifOutput.append([token, counter])
            elif token in self.separators:
                position = -1
                if token in [":", ";"]:
                    position = -1
                self.pifOutput.append([token, position])
            elif re.match(r'^[+-]?[1-9][0-9]*|0$', token):
                position = self.intConstantsST.insert_integer(token, int(token))
                self.pifOutput.append(["CONSTANT", position_counter])
                position_counter += 1  # Increment the shared position counter
            elif re.match(r'^[a-zA-Z_][a-zA-Z0-9_]*$', token):
                if token not in identifiers:
                    identifiers[token] = position_counter
                position = self.identifiersST.insert_identifier(token, token)
                self.pifOutput.append(["IDENTIFIER", position_counter])
                position_counter += 1  # Increment the shared position counter
            elif token.startswith('"'):
                if token.endswith('"'):
                    position = self.strConstantsST.insert_string(token, token[1:-1])
                    self.pifOutput.append(["STRING_CONSTANT", position_counter])
                    position_counter += 1  # Increment the shared position counter
                else:
                    in_quoted_string = True
            else:
                print(f"Invalid token: {token} on line {counter}")
                lexical_error_exists = True
        if not in_quoted_string:
            print("Program is lexically correct!")

        # Print identifiers with their indices
        for idx, (identifier, index) in enumerate(identifiers.items()):
            print(f"{index}:{identifier} is an identifier {idx}")

    def find_token_index(self, target_token):
        with open('token.in', 'r') as file:
            for line in file:
                line = line.strip()
                if target_token in line:
                    index = line.split()
                    return index[0]

    def get_pif(self):
        return self.pifOutput

    def get_constantST(self):
        return self.intConstantsST

    def get_identifiersST(self):
        return self.identifiersST
