import unittest
from src.a4.a4 import Board

class A4Test(unittest.TestCase):

    def test_populate_rows(self):
        board = Board()

        board.populate_rows('123\n321')

        self.assertEqual(
            [
                ['1', '2', '3'],
                ['3', '2', '1'],
            ],
            board.rows
        )

    def test_run(self):
        board = Board([
            [0, 0, 1, 0],
            [0, 0, 0, 0],
            [2, 2, 2, 0]
        ])

        self.assertEqual(2, board.run())

    def test_color_area(self):
        board = Board()

        board.rows = [
            [0, 0, 0],
            [0, 0, 1],
            [0, 0, 0]
        ]

        board.color_area(1, 1, 2)

        self.assertEqual(
            [
                [2, 2, 2],
                [2, 2, 1],
                [2, 2, 2]
            ],
            board.rows
        )

    def test_run_example(self):
        board = Board()
        board.populate_rows(
            '1346242331\n'
            '1243222445\n'
            '1442323455\n'
            '4465555554\n'
            '4351525153\n'
            '2155515533\n'
            '5555555555\n'
            '5256545354\n'
            '1623233266\n'
            '6613412455'
        )

        self.assertEqual(17, board.run())
if __name__ == '__main__':
    unittest.main()
