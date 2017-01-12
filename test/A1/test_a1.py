import unittest
from src.a1.a1 import get_square


class A1Test(unittest.TestCase):

    def test_size_0(self):
        """"A square with the size of 0 should just yield an empty result"""
        self.assertEqual("", get_square(0))

    def test_size_1(self):
        """"A square with the size of 1 should only yield a single '*'"""
        self.assertEqual("*\n", get_square(1))

    def test_size_2(self):
        """A square of 2 should should just be 2x2 '*' without the inner '-'"""
        self.assertEqual('**\n**\n', get_square(2))

    def test_size_3(self):
        """A square of three is the first that actually has '-' on the inside"""
        self.assertEqual('***\n*-*\n***\n', get_square(3))

if __name__ == '__main__':
    unittest.main()
