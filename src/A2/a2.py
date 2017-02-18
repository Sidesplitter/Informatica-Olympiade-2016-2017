import re


def remove_vowels(string=''):
    """
    Removes the vowels from the given string.
    According to the rules the letters A, E, I, O, U are considered vowels.
    :param string: The input to remove vowels from
    :return: The given string without vowels
    """
    return re.sub('a|e|i|o|u|y', '', string, flags=re.IGNORECASE)


def main():
    string = input()

    print(remove_vowels(string))


if __name__ == '__main__':
    main()
