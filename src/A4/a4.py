
class Board:
    def __init__(self, rows=None):

        if rows is None:
            rows = []

        self.rows = rows

    def populate_rows(self, data=""):
        """
        Populate all the rows based on the data, rows are separated by a newline (\n)
        :param data:
        :return:
        """
        for row in data.splitlines():

            self.rows.append(list(row))

    def run(self):
        """
        Returns how many turns it takes to give all the items the same color based on the rules
        :return:
        """
        turns = 0

        # Iterate over the rows
        for row in self.rows:

            # Iterate over the columns
            for col in row:

                # Different color, color the base area
                if col != self.get_base_color():

                    self.color_area(0, 0, col)
                    turns += 1

        return turns

    def get_base_color(self):

        return self.rows[0][0]

    def color_area(self, row, col, color):
        """
        Colors the area starting at the given coordinate
        The area consists of the item at the given coordinate and all the adjacent items that also have the same color
        as the item at the starting coordinate
        :param row: The row where the item is in (Y)
        :param col: The column where the item is in (X)
        :param color: The color to color the area with
        :return:
        """
        old_color = self.rows[row][col]

        self.rows[row][col] = color

        # 1 Above
        if row - 1 >= 0 and self.rows[row - 1][col] == old_color:
            self.color_area(row - 1, col, color)

        # 1 Below
        if row + 1 < len(self.rows) and self.rows[row + 1][col] == old_color:
            self.color_area(row + 1, col, color)

        # 1 Left
        if col - 1 >= 0 and self.rows[row][col - 1] == old_color:
            self.color_area(row, col - 1, color)

        # 1 Right
        if col + 1 < len(self.rows[row]) and self.rows[row][col + 1] == old_color:
            self.color_area(row, col + 1, color)


def main():
    board = Board()

    data = ""

    # Get 10 rows
    for i in range(0, 10):
        data += input() + '\n'

    data.strip()

    board.populate_rows(data)

    print(board.run())

if __name__ == '__main__':
    main()
