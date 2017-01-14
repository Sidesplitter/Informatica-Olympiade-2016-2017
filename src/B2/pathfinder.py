from typing import Tuple

from B2.world import World


class PathFinder:
    """
    This PathFinder is a modified version of a standard A* pathfinder.

    Since we want the longest path, and not the shortest, we can not copy A* one on one, as it is designed for the
    shortest path. The only true way to get the longest path is to check every single coordinate on the board.

    See https://en.wikipedia.org/wiki/Longest_path_problem#NP-hardness

    """
    starting_coordinates = None
    """
    :type from_coordinates: (int, int)
    """

    destination_coordinates = None
    """
    :type destination_coordinates: (int, int)
    """

    world = None
    """
    :type world: World
    """

    def __init__(self, starting_coordinates: Tuple[int, int], destination_coordinates: Tuple[int, int], world: World):
        """

        :param (int, str) starting_coordinates:
        :param (int, str) destination_coordinates:
        :param World world:
        """
        self.starting_coordinates = starting_coordinates
        self.destination_coordinates = destination_coordinates
        self.world = world

    def get_path(self):
        """

        :return: The path to follow
        :rtype: list[(int, int)]
        """
        # Closed set contains coordinates we still have to calculate
        closed_set = []

        # Open set contains coordinates we have already calculated
        open_set = []

        # Cost to reach the node
        cost_to_node = {self.starting_coordinates: 0}

        # To make sure that we pass every coordinate, append all of the coordinates to the open set
        for y in range(0, self.world.height):
            for x in range(0, self.world.width):
                open_set.append((y, x))

        came_from = {self.starting_coordinates: None}  # type: dict[(int, int), (int, int) | None)

        while len(open_set) > 0:

            # Find the node with the highest cost to the destination
            current = open_set[0]

            open_set.remove(current)
            closed_set.append(current)

            for neighbor in self.get_neighbors(current):

                # The cost to get to the neighbour, is our current cost plus the cost of the neighbor
                cost = cost_to_node[current] + self.world.get_value(neighbor)

                # We already calculated this
                if neighbor in closed_set:
                    continue

                # We have a new point to calculate
                if neighbor not in open_set:
                    open_set.append(neighbor)

                # We already have this neighbor with a higher cost
                elif neighbor in cost_to_node and cost <= cost_to_node[neighbor]:
                    continue

                cost_to_node[neighbor] = cost
                came_from[neighbor] = current

        return self.generate_path(came_from, self.destination_coordinates)

    @staticmethod
    def generate_path(came_from, current):
        """

        :param dict[(int, int), (int, int) | None] came_from:
        :param (int, int) current:
        :return:
        :rtype: list[(int, int)]
        """

        path = [current]

        while current in came_from.keys():

            current = came_from[current]

            # We are at the source
            if current is None:
                break

            path.append(current)

        # Reverse it, so that the first move is at the front
        path.reverse()

        return path

    def get_neighbors(self, coordinates):
        """
        Finds all the possible coordinates a piece can move to from the given coordinates.

        :param (int, int) coordinates: The coordinates for which we are finding neighbors
        :return:
        :rtype: list[(int, int)]
        """

        neighbors = []

        # Go down if possible
        # We can only go down if our current X coordinate is even (=> A horizontal row)
        if coordinates[1] % 2 == 0 and coordinates[0] + 1 < self.world.height:
            neighbors.append((coordinates[0] + 1, coordinates[1]))

        # Go right if possible
        # We can only go right if our current Y coordinate is even (=> A vertical row)
        if coordinates[0] % 2 == 0 and coordinates[1] + 1 < self.world.width:
            neighbors.append((coordinates[0], coordinates[1] + 1))

        return neighbors
