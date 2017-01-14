from B3.world import World


def main():
    world = World('world.yml')
    world.can_build_lake((0, 1), (3, 4))
    largest = world.largest_rectangle

    print("The largest rectangle has a size of {length}, starts at {start} and ends at {end}".format(
        length=world.get_lake_size(largest[0], largest[1]),
        start=largest[0],
        end=largest[1]
    ))

if __name__ == '__main__':
    main()