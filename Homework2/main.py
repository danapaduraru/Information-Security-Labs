"""
Scrieti un program ce utilizeaza API EVP pentru implementarea functiilor hash.
Programul va primi ca intrare doua fisiere text, f_1 si f_2, ce au acelasi continut, cu exceptia unui singur caracter.
Programul va calcula functiile hash asociate celor doua fisiere, utilizand algoritmii MD5 si SHA256,
rezultand  hash-urile   h1_md5,   h2_md5, respectiv h1_sha256,   h2_sha256.
De asemenea, programul va compara fisierele rezultate pentru  fiecare algoritm in parte, adica:
h1_md5  va  fi comparat  cu  h2_md5, iar h1_sha256 va fi comparat cu h2_sha256
(la nivel de octeti si va afisa numarul de octeti identici in cele doua fisiere)
"""

import hashlib

"""
    encode() : Converts the string into bytes to be acceptable by hash function.
    digest() : Returns the encoded data in byte format.
    hexdigest() : Returns the encoded data in hexadecimal format.
"""

"""
1. get files
2. get hash for each function: md5
3. get hash for each function: sha256
4. compare bytes
5. compare number of identical bytes in each of the files.
"""


def get_text_from_file(file_name):
    f = open(file_name, "r")
    text = f.read()
    return text


def get_md5_hash(file_content):
    hash_md5_result = hashlib.md5(file_content.encode('utf-8')).digest()
    print("Hash for: " + file_content)
    print(hash_md5_result)
    print()
    return hash_md5_result


def get_sha256_hash(file_content):
    sha256_result = hashlib.sha256(file_content.encode('utf-8')).digest()
    print("Hash for: " + file_content)
    print(sha256_result)
    print()
    return sha256_result


def get_identical_bytes(string1, string2):
    identical_bytes_count = 0
    for byte in string1:
        if byte in string2:
            identical_bytes_count += 1
    print("Number of identical bytes: " + str(identical_bytes_count))


file_1_name = "file1.txt"
file_2_name = "file2.txt"

if __name__ == '__main__':
    print("==================== MD5 ====================")
    file_1 = get_text_from_file(file_1_name)
    file_2 = get_text_from_file(file_2_name)
    md5_h1 = get_md5_hash(file_1)
    md5_h2 = get_md5_hash(file_2)
    get_identical_bytes(md5_h1, md5_h2)
    print()

    print("==================== SHA256 ====================")
    sha256_h1 = get_sha256_hash(file_1)
    sha256_h2 = get_sha256_hash(file_2)
    get_identical_bytes(sha256_h1, sha256_h2)



