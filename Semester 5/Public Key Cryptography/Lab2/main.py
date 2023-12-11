from bellaso import bellaso_encrypt, bellaso_decrypt

keyword = 'berries'

to_encrypt = 'She bought herself flowers'
encrypted_msg = bellaso_encrypt(to_encrypt, keyword)
print(f'\nBellaso cipher encryption:\n{encrypted_msg}\n')


to_decrypt = 'Sii sfckzu lviaidg jcfeijt'
decrypted_msg = bellaso_decrypt(to_decrypt, keyword)
print(f'Bellaso cipher decryption:\n{decrypted_msg}')

