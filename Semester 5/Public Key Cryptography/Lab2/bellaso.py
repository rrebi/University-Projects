
def bellaso_encrypt(msg, key):
    """
    uses a key and the alphabet to encrypt the message. polyalphabetic substitution
    :param msg: the msg to be encrypted
    :param key: the keyword used for encryption
    :return: encrypted msg
    """
    encoded = ''  # encrypted msg
    alph = 'abcdefghijklmnopqrstuvwxyz'
    offset = 0

    # iterates through each character
    for i in range(len(msg)):

        # if not letter => no need to encrypt
        if msg[i] not in alph:
            output = msg[i]
            offset -= 1

        # letter
        # p1 = finds position of character in the alphabet
        # p2 = finds position of character in the keyword
        else:
            p1 = alph.find(msg[i])
            p2 = alph.find(key[((i + offset) % len(key))])

            # needs wrapping around the alphabet (p1 + p2 > 25)
            if p1 > (len(alph) - p2 - 1):
                # finds the alphabetical character of (p1 + p2) % 26
                output = alph[(p1 + p2) % 26]

            # no wrapping
            else:
                # finds the alphabetical character of (p1 + p2)
                output = alph[p1 + p2]

        # add character to the string
        encoded += output
    return encoded


def bellaso_decrypt(msg, key):
    """
    uses a key and the alphabet to decrypt the message. polyalphabetic substitution
    :param msg: the msg to be decrypted
    :param key: the keyword used for decryption
    :return: decrypted msg
    """
    decrypted = ''
    alph = 'abcdefghijklmnopqrstuvwxyz'
    offset = 0

    # iterates through each character
    for i in range(len(msg)):

        # if not letter => no need to decrypt
        if msg[i] not in alph:
            output = msg[i]
            offset -= 1

        # letter
        # p1 = finds position of character in the alphabet
        # p2 = finds position of character in the keyword
        else:
            p1 = alph.find(msg[i])
            p2 = alph.find(key[((i + offset) % len(key))])

            # needs wrapping around the alphabet (p1 + p2 > 25)
            if p1 > (len(alph) - p2 - 1):
                # finds the alphabetical character of (p1 - p2) % 26
                output = alph[(p1 - p2) % 26]

            # no wrapping
            else:
                # finds the alphabetical character of (p1 - p2)
                output = alph[p1 - p2]

        # add character to string
        decrypted += output
    return decrypted
