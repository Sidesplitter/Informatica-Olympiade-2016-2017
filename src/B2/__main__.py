from B2.pathfinder import PathFinder
from B2.world import World


def main():
    world = World('world.yml')
    path_finder = PathFinder((0, 0), (world.height - 1, world.width - 1), world)
    path = path_finder.get_path()
    total = sum(map(lambda coordinates: world.get_value(coordinates), path))

    readable_coordinates = list(map(lambda coordinates: (coordinates[1], coordinates[0]), path))
    print("Path that was taken (X, Y): {}".format(readable_coordinates))

    print("Total amount of streets passed: {}".format(int((len(path) - 1) / 2)))
    print("Maximum amount of houses: {}".format(total))


if __name__ == '__main__':
    main()
