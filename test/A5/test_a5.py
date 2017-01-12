import unittest
import logging
import sys
from src.a5.a5 import Node, NodeManager


class A5Test(unittest.TestCase):

    def setUp(self):
        logging.basicConfig(stream=sys.stdout, format='%(levelname)s: %(message)s', level=logging.DEBUG)

    def test_add_connection(self):
        """
        Test connecting nodes to each other
        :return:
        """

        # 1 - 2
        node1 = Node('1')
        node2 = Node('2')

        node1.add_connection(node2)

        self.assertTrue(node1 in node2.connections)
        self.assertTrue(node2 in node1.connections)

    def test_get_distance_two_nodes(self):
        """
        Test the distance for two nodes
        :return:
        """

        # 1 - 2
        node1 = Node('1')
        node2 = Node('2')

        node1.add_connection(node2)

        self.assertEqual(1, node1.get_distance(node2))

    def test_get_distance_three_nodes(self):
        """
        Test the distance for more than two nodes
        :return:
        """

        # 1 - 2 - 3
        node1 = Node('1')
        node2 = Node('2')
        node3 = Node('3')

        node1.add_connection(node2)
        node2.add_connection(node3)

        self.assertEqual(2, node1.get_distance(node3))

    def test_get_distance_dead_end(self):
        """
        We encountered a bug with this setup where retrieving the distance from 6 to 1 would result into a 4
        This happened because 1 would not put itself on the traversed list, which caused node 2 to return to 1
        :return:
        """
        # 2       6
        #  \     /
        #   1 - 4
        #  /     \
        # 3       5
        node1 = Node('1')
        node2 = Node('2')
        node3 = Node('3')
        node4 = Node('4')
        node5 = Node('5')
        node6 = Node('6')

        node1.add_connection(node2)
        node1.add_connection(node3)
        node4.add_connection(node1)
        node4.add_connection(node5)
        node4.add_connection(node6)

        self.assertEqual(2, node6.get_distance(node1))

    def test_get_distance_none(self):
        """
        Test that the distance returns none when there is no connection
        :return:
        """
        node1 = Node('1')
        node2 = Node('2')

        self.assertEqual(None, node1.get_distance(node2))

    def test_get_largest_distance(self):
        """
        Tests the largest distance from node1 to any of the specified nodes
        :return:
        """

        # 1 - 3
        # |   |
        # 2   4
        node1 = Node('1')
        node2 = Node('2')
        node3 = Node('3')
        node4 = Node('4')

        node1.add_connection(node2)
        node1.add_connection(node3)
        node3.add_connection(node4)

        self.assertEqual(2, node1.get_largest_distance([node2, node3, node4]))

    def test_get_central_nodes(self):

        #   1
        # / | \
        # 2 3 3
        node1 = Node('1')
        node2 = Node('2')
        node3 = Node('3')
        node4 = Node('4')

        node1.add_connection(node2)
        node1.add_connection(node3)
        node1.add_connection(node4)

        manager = NodeManager([node1, node2, node3, node4])
        central_nodes = manager.get_central_nodes()

        self.assertEqual(1, len(central_nodes))
        self.assertIn(node1, central_nodes)

    def test_get_central_nodes_multiple(self):

        # 2       6
        #  \     /
        #   1 - 4
        #  /     \
        # 3       5
        node1 = Node('1')
        node2 = Node('2')
        node3 = Node('3')
        node4 = Node('4')
        node5 = Node('5')
        node6 = Node('6')

        node1.add_connection(node2)
        node1.add_connection(node3)
        node4.add_connection(node1)
        node4.add_connection(node5)
        node4.add_connection(node6)
        node6.get_distance(node2)

        manager = NodeManager([node1, node2, node3, node4, node5, node6])

        central_nodes = manager.get_central_nodes()
        self.assertEqual(2, len(central_nodes))
        self.assertIn(node1, central_nodes)
        self.assertIn(node4, central_nodes)


if __name__ == '__main__':
    unittest.main()
