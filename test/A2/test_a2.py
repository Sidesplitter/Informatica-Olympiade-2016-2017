import unittest
from src.a2.a2 import remove_vowels


class A2Test(unittest.TestCase):

    def test_lowercase(self):
        self.assertEqual('n', remove_vowels('aeioun'))

    def test_uppercase(self):
        self.assertEqual('N', remove_vowels('AEIOUN'))

    def test_remove_vowels(self):
        self.assertEqual('vrgtmjntj', remove_vowels('vergeetmijnietje'))


if __name__ == '__main__':
    unittest.main()
