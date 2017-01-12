def get_collatz(integer):

    if integer == 1:
        return integer

    if integer % 2 == 0:
        integer /= 2
    else:
        integer = integer * 3 + 1

    return integer


def get_largest_collatz(integer):

    largest = integer

    while integer != 1:
        integer = get_collatz(integer)
        largest = max(integer, largest)

    return largest


def main():
    integer = int(input())

    print(round(get_largest_collatz(integer)))


if __name__ == '__main__':
    main()
