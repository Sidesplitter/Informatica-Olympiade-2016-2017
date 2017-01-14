from typing import Tuple

import yaml


class World:

    world = None
    """
    The first index is the Y coordinate, and the second index is the X coordinate
    :type world: List[List[int]]
    """

    width = None
    """
    :type width: int
    """

    height = None
    """
    :type height: int
    """

    def __init__(self, path):
        self.world = []
        self.load(path)

    def is_free(self, coordinates: Tuple[int, int]):
        return self.world[coordinates[0]][coordinates[1]] == 0

    def can_build_lake(self, first_coordinates: Tuple[int, int], second_coordinates: Tuple[int, int]) -> bool:
        """
        Checks if it is possible to build a like between those two coordinates
        :param Tuple[int, int] first_coordinates:
        :param Tuple[int, int] second_coordinates:
        :return: True if the space is free, false if there is at least something there on one of those spots
        :rtype: bool
        """
        for x in range(
                min(first_coordinates[0], second_coordinates[0]),
                max(first_coordinates[0], second_coordinates[0]) + 1
        ):
            for y in range(
                    min(first_coordinates[1], second_coordinates[1]),
                    max(first_coordinates[1], second_coordinates[1]) + 1
            ):
                if not self.is_free((x, y)):
                    return False

        return True

    @staticmethod
    def get_lake_size(first_coordinates: Tuple[int, int], second_coordinates: Tuple[int, int]) -> int:
        # Since our coordinate system starts at when, we have to increase the length by one.
        # After that it is just width * height
        return (abs(first_coordinates[0] - second_coordinates[0]) + 1) * \
               (abs(first_coordinates[1] - second_coordinates[1]) + 1)

    def load(self, path: str) -> None:
        self.world = []

        with open(path, 'r') as f:
            yml = yaml.load(f)

        self.height = yml['info']['height']
        self.width = yml['info']['width']

        # Create an empty world
        for x in range(0, self.width):
            self.world.append([])
            for y in range(0, self.height):
                self.world[x].append(0)

        for house in yml['data']:
            self.world[house[0]][house[1]] = 1

    @property
    def largest_rectangle(self) -> Tuple[Tuple[int, int], Tuple[int, int]]:
        """
        Returns the largest rectangle in the world.

        Yes I know that this calculates the largest rectangle every time we call this property but for this exercise
        this is more than good enough
        :return:
        :rtype: Tuple[Tuple[int, int], Tuple[int, int]]
        """

        largest = 0
        largest_first_coordinates = None
        largest_second_coordinates = None

        for start_y in range(0, self.height):

            for start_x in range(0, self.width):

                first_coordinates = (start_x, start_y)

                # This spot is not free, just skip it
                if not self.is_free(first_coordinates):
                    continue

                for end_x in range(start_x, self.width):

                    for end_y in range(start_y, self.height):

                        second_coordinates = (end_x, end_y)

                        # The second coordinate is not free, we do not need to go down further since there is
                        # something in the way
                        if not self.is_free(second_coordinates):
                            break

                        # We cannot build a lake in this rectangle
                        # We do not have to go down further, since there is already something in the way
                        if not self.can_build_lake(first_coordinates, second_coordinates):
                            break

                        size = self.get_lake_size(first_coordinates, second_coordinates)

                        if size > largest:
                            largest = size
                            largest_first_coordinates = first_coordinates
                            largest_second_coordinates = second_coordinates

        return largest_first_coordinates, largest_second_coordinates
