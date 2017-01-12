import unittest
from src.a3.a3 import get_collatz, get_largest_collatz

class A3Test(unittest.TestCase):

    def test_get_collatz_1(self):
        self.assertEqual(1, get_collatz(1))

    def test_get_collatz_even(self):
        self.assertEqual(2, get_collatz(4))

    def test_get_collatz_odd(self):
        self.assertEqual(10, get_collatz(3))

    def test_get_largest_collatz(self):
        self.assertEqual(52, get_largest_collatz(14))

if __name__ == '__main__':
    unittest.main()
