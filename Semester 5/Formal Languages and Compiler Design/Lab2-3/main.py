from Scanner import Scanner
def run(file_path):
    scanner = Scanner(file_path)
    scanner.scan()
    pif = scanner.get_pif()

    with open(file_path + ".pif.txt", 'w') as file:
        for element in pif:
            file.write(str(element) + '\n')

    constST = scanner.get_constantST()
    idST = scanner.get_identifiersST()

    # Write the Integer Constants table to the file
    with open(file_path + ".tables.txt", 'w') as file:
        file.write("Integer Constants table starts here:\n")
        for index, value in constST.int_hash_table.items():
            file.write(f"{index}: {value}\n")

    # Write the String Constants table to the file
    with open(file_path + ".tables.txt", 'a') as file:
        file.write("String Constants table starts here:\n")
        for index, value in constST.str_hash_table.items():
            file.write(f'{index}: "{value}"\n')

    # Write the Identifiers table to the file
    with open(file_path + ".tables.txt", 'a') as file:
        file.write("Identifiers table starts here:\n")
        for index, value in idST.identifier_hash_table.items():
            file.write(f"{index}: {value}\n")

if __name__ == "__main__":
    run("p1.txt")
    run("p2.txt")
    run("p3.txt")
    run("p1ERR.txt")
