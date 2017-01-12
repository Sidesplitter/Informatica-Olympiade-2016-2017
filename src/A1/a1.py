def get_square(size=0):
    """
    Returns a drawn square with '*' as the border and '-' on the inside of the square
    :param size: The size of the square
    :return: A ASCII square
    """

    output = ''
    for i in range(0, size):

        # The first and the last row only contain '*'
        if i == 0 or i == size - 1:
            output += '*' * size + '\n'
            continue

        output += '*' + ('-' * (size - 2)) + '*\n'

    return output


def main():
    size = int(input())

    print(get_square(size))


if __name__ == '__main__':
    main()
