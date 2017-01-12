import logging

class Node:
    def __init__(self, name=""):

        self.name = name
        self.connections = list()
        self.logger = logging.getLogger('a5.node')

    def add_connection(self, node):
        """
        Add a connection to this node, also adds it it the other way around

        :param node: The node to add
        :type node: Node

        :return:
        """
        self.connections.append(node)
        node.connections.append(self)

    def get_distance(self, node, traversed=None):
        """
        Returns the distance between this node and its children

        :param traversed: A list of nodes that have already been searched and should not be searched again.
        :type traversed: list[Node]
        :param node: The node to check the distance for
        :type node: Node

        :return: The distance between this not and the given node
        :rtype: int | None
        """
        self.logger.debug('Iterating over {}'.format(self.name))
        if traversed is None:
            traversed = []

        # We are checking for ourselves
        if node == self:
            return 0

        # We are a direct connection
        if node in self.connections:
            self.logger.debug('Found distance 1 between node {} and {}'.format(node.name, self.name))
            return 1
        else:
            # Check if the children have a connection
            for n in self.connections:

                if n in traversed:
                    continue

                self.logger.debug('Following {} to {}'.format(self.name, n.name))

                traversed.append(self)
                dist = n.get_distance(node, traversed)

                # The child has a connection
                if dist is not None:
                    self.logger.debug('Found distance {} between node {} and {}'.format(dist + 1, self.name, node.name))
                    return 1 + dist

        return None

    def get_largest_distance(self, nodes, cache=None):
        """
        Calculate the average distance between this Node and all the given nodes. Optionally you can specify a cache
        To speed up the operation, The cache works both ways because of |AB| = |BA|.

        :param cache: The cache contains already calculated value. The key is node1_node2
        :type cache: dict[str, int]
        :param nodes: A list with nodes to compare against
        :type nodes: list[Node]

        :return: The largest distance
        :rtype: int
        """
        if cache is None:
            cache = {}

        distance = 0

        for node in nodes:

            if node == self:
                continue

            # The cache name can be in both ways
            if node.name + "_" + self.name in cache:
                cache_name = node.name + "_" + self.name
            else:
                cache_name = self.name + "_" + node.name

            if cache_name in cache:
                dist = cache[cache_name]
                self.logger.debug('Found {} in cache: {}'.format(cache_name, dist))
            else:
                self.logger.debug('Calculating distance between {} and {}'.format(self.name, node.name))
                dist = node.get_distance(self)
                cache[cache_name] = dist

            distance = max(distance, dist)

            self.logger.debug('New max distance for {} is {}'.format(self.name, distance))

        return distance


class NodeManager:
    def __init__(self, nodes=None):
        """
        :param nodes: A list of nodes to manage
        :type nodes: list[Node]
        """
        if nodes is None:
            self.nodes = list()
        else:
            self.nodes = nodes

    def get_central_nodes(self):
        """

        :return: A list of nodes that lie in the center of all the nodes
        :rtype: list[Node]
        """
        central_nodes = []
        closest_distance = 0

        cache = {}

        for node in self.nodes:

            distance = node.get_largest_distance(self.nodes, cache)

            # It is closer than the previous one, clear the list
            if distance < closest_distance:
                central_nodes = []

            # It is at least as close, add it to the list
            if distance <= closest_distance or closest_distance == 0:
                central_nodes.append(node)
                closest_distance = distance

        return central_nodes

    def get_node_by_name(self, name):
        """
        Retrieve a node by name

        :param name: The name of the node
        :param name: str

        :return: The node asked for, or None if the node was not found
        :rtype: Node | None
        """
        items = list(filter(lambda node: node.name == name, self.nodes))

        return items[0] if items else None

    def populate_nodes(self, data):
        """

        :param data: Lines separated by a newline. Each line contains two nodes separated by a space.
        :type data: str

        :return:
        """
        for string in data.splitlines():

            n1, n2 = string.split(' ')

            if self.get_node_by_name(n1) is None:
                node = Node(name=n1)
                self.nodes.append(node)

            if self.get_node_by_name(n2) is None:
                node = Node(name=n2)
                self.nodes.append(node)

            self.get_node_by_name(n1).add_connection(self.get_node_by_name(n2))


def main():
    amount_nodes = int(input()) - 1
    nodes = ""

    for i in range(0, amount_nodes):
        nodes += input() + '\n'

    manager = NodeManager()
    manager.populate_nodes(nodes)

    output = ""

    for node in manager.get_central_nodes():
        output += node.name + " "

    print(output.strip())


if __name__ == '__main__':
    main()
