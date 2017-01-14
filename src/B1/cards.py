from typing import List

import math


class Cards:

    top_row = None
    """
    :type topRow: List[int]
    """

    bottom_row = None
    """
    :type bottom_row: List[int]
    """

    def __init__(self, top_row: List[int], bottom_row: List[int]):

        self.top_row = top_row
        self.bottom_row = bottom_row

    @property
    def sorted(self) -> bool:
        for index in range(1, len(self.top_row)):
            if self.top_row[index - 1] > self.top_row[index]:
                return False
        return True

    def clone(self) -> Cards:
        return Cards(self.top_row, self.bottom_row)

    def can_be_sorted_at_turn(self, turn) -> bool:

        sorted_bottom = sorted(self.bottom_row[:turn])
        inserts = len(self.top_row) - turn
        maximum_gap = math.ceil((len(self.top_row) - turn) / 2)

        cards = self.clone()

        for i in range(0, inserts):

            for gap in range(0, maximum_gap):
                pass


        # for item in sorted_bottom:
        #     cards = self.clone()
        #
        #     for gap in range(0, maximum_gap):
        #         c = cards.clone()
        #         index = gap
        #
        #         # Swap the items
        #         c.bottom_row[c.bottom_row.index(item)] = c.top_row[index]
        #         c.top_row[index] = item
        #
        #         if c.sorted:
        #             return True

        return False

