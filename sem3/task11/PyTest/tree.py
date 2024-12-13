# B-tree implementation in Python

class TreeNode:
    id = -1
    values = []
    children = []
    volume = 0

    def __init__(self):
        self.id = -1
        self.values = []
        self.children = []
        self.volume = 0

    def allocate(self, m: int):
        self.values = [[] for i in range(2 * m)]
        self.children = [None for i in range(2 * m + 1)]
        self.volume = 0

    def __str__(self):
        return str(self.values[:self.volume])
    
    def __len__(self):
        return self.volume

    def insert(self, value, down, index):
        for i in range(self.volume, index, -1):
            self.values[i] = self.values[i - 1]
            self.children[i + 1] = self.children[i]
        self.values[index] = value
        self.children[index + 1] = down
        self.volume += 1
    
    def bin_search(self, value):
        left = 0 
        right = self.volume - 1

        while left < right:
            middle = (left + right) // 2

            if self.values[middle] <= value:
                left = middle + 1
            else:
                right = middle
        if left == right and self.values[left] <= value:
            return left + 1
        return left 

    def children_count(self):
        if self.volume == 0:
            return 0
        if self.children[0] == None:
            return 0
        return self.volume + 1


def correct_int(num: int) -> int:
    if num >= pow(2, 63):
        return -1
    if num < -pow(2, 63):
        return 0
    num =  num % pow(2, 32)
    if num >= pow(2, 31):
        num = num - pow(2, 32)
    return num

class Tree:
    root = None 
    nodes = []
    links = []
    capacity = 0
    m = 0

    def __init__(self):
        self.root = None
        self.nodes = []
        self.links = []
        self.capacity = -1
        self.m = 0

    def factory_reset(self):
        self.root = None
        self.nodes = []
        self.links = []
        self.capacity = -1
        self.m = 0


    def add_value(self, new_value):
        if self.root is None:
            self.root = TreeNode()
            self.root.allocate(self.m)
            self.root.insert(new_value, None, 0)
            return
        
        curr = self.root
        res = self.add_into_subtree(curr, new_value, self.m)
        if res[0] == "success":
            return

        new_root = TreeNode()
        new_root.allocate(self.m)
        new_root.insert(res[2], res[1], 0)
        new_root.children[0] = curr

        self.root = new_root

    
    def add_into_subtree(self, current_node : TreeNode, new_value, m):
        index = current_node.bin_search(new_value)
        child_node = current_node.children[index]

        if child_node is not None:
            # child exists
            status = self.add_into_subtree(child_node, new_value, m)
            if status[0] == "success":
                return ["success", None]
            down_node = status[1]
            new_value = status[2]
            # otherwise a new node was created
            # it's contained in 'down_node'
        else:
            down_node = None

        if current_node.volume < 2 * m:
            # we have enough space in the current node
            current_node.insert(new_value, down_node, index)
            return ["success", None]

        node = TreeNode()
        node.allocate(m)

        if index == m:
            # precisely in the center
            # move the second part into a new node
            for i in range(1, m + 1):
                node.values[i - 1] = current_node.values[i + m - 1]
                node.children[i] = current_node.children[i + m]
                current_node.children[i + m] = None
            # the smallest, but greater than 'new_value'
            node.children[0] = down_node

        if index < m:
            # in the first part
            # move the second part into a new node
            for i in range(m):
                node.values[i] = current_node.values[i + m]
                node.children[i] = current_node.children[i + m]
                current_node.children[i + m] = None
            node.children[m] = current_node.children[2 * m]
            current_node.children[2 * m] = None

            # move elements to the right
            # and insert 'new_value' in position 'index'
            for i in range(m, index, -1):
                current_node.values[i] = current_node.values[i - 1]
                current_node.children[i + 1] = current_node.children[i]
            current_node.children[index + 1] = down_node
            current_node.values[index] = new_value
            new_value = current_node.values[m]
            # 'new_value' is a new maximal

        if index > m:
            # in the second part
            # move the second part until 'index'
            # into a new node
            node.children[0] = current_node.children[m + 1]
            current_node.children[m + 1] = None
            for i in range(1, index - m):
                node.values[i - 1] = current_node.values[i + m]
                node.children[i] = current_node.children[i + m + 1]
                current_node.children[i + m + 1] = None

            # insert 'new_value'
            node.values[index - m - 1] = new_value
            node.children[index - m] = down_node

            # move other element from the second part
            # into a new node
            for i in range(index - m + 1, m + 1):
                node.values[i - 1] = current_node.values[i + m - 1]
                node.children[i] = current_node.children[i + m]
                current_node.children[i + m] = None

            # new maximal
            new_value = current_node.values[m]

        down_node = node
        node.volume = m
        current_node.volume = m
        return ["create", down_node, new_value]   

    def fill_nodes(self, node, index):
        if node is None:
            return index

        self.nodes.append(node)
        node.id = index
        index += 1

        for elem in node.children:
            index = self.fill_nodes(elem, index)
        return index

    def connect_links(self):
        for i in range(len(self.nodes)):
            self.links += [[node.id for node in self.nodes[i].children if node is not None]]
            
    def read_from_file(self, file_name, m):
        file = open(file_name, "r")
        data = file.readlines()
        file.close()

        self.capacity = 0
        self.m = m
        for elem in data:
            if len(elem.split()) != 2:
                self.factory_reset()
                return
            if not(elem.split()[1].lstrip("-").isdigit()):
                self.factory_reset()
                return
            #print(int(elem.split()[1]), correct_int(int(elem.split()[1])))
            value = [[elem.split()[0], correct_int(int(elem.split()[1]))]]
            self.add_value(value)
        
        self.fill_nodes(self.root, 0)
        self.connect_links()

    # ------------------------
    
    def print_subtree(self, node : TreeNode, level):
        if node is None:
            return
        
        print ("  " * level, end ="")
        print(node)
        for elem in node.children:
            self.print_subtree(elem, level + 1)
            
    def print_tree(self):
        self.print_subtree(self.root, 0)

    # ------------------------
    
    def size(self):
        return len(self.nodes)
    
    def volume(self):
        return sum([node.volume for node in self.nodes])

    def children_count(self):
        return [len(self.links[i]) for i in range(len(self.links))]
    
    def subtrees_sizes(self):
        sizes = [1] * (self.size() + 1)
        sizes[-1] = 0
        for i in range(self.size() - 1, -1, -1):
            for id in self.links[i]:
                sizes[i] += sizes[id]
        return sizes[:-1]
    
    def subtrees_depths(self):
        depths = [1] * (self.size() + 1)
        depths[-1] = 0
        for i in range(self.size() - 1, -1, -1):
            for id in self.links[i]:
                depths[i] = max(depths[id] + 1, depths[i])
        return depths[:-1]

    def level_decomposition(self):
        levels = []

        if self.size() == 0:
            return []

        levels = [[0]]
        level = 0
        while levels[level] != []:
            levels += [[]]
            for i in levels[level]:
                levels[level + 1].extend(self.links[i])
            level += 1
            
        return levels[:-1]

    # -----------------------------------
    
    # task 1
    def k_children_volume(self, k: int) -> int:
        return sum([node.volume for node in self.nodes if node.children_count() == k])
    
    # task 2
    def k_size(self, k: int) -> int:
        sizes = self.subtrees_sizes()
        return sum([self.nodes[i].volume for i in range(self.size()) if sizes[i] <= k])
    
    # task 3
    def k_depth(self, k: int) -> int:
        depths = self.subtrees_depths()
        return sum([self.nodes[i].volume for i in range(self.size()) if depths[i] <= k])
    
    # task 4
    def k_subtrees(self, k: int) -> int:
        depths = self.subtrees_depths()
        last_level_sizes = [0 for i in range(self.size())]

        for i in range(self.size() - 1, -1, -1):
            if self.links[i] == []:
                last_level_sizes[i] = 1
            for id in self.links[i]:
                if depths[id] + 1 == depths[i]:
                    last_level_sizes[i] += last_level_sizes[id]

        count = 0
        for i in range(self.size()):
            if last_level_sizes[i] <= k:
                count += self.nodes[i].volume
        
        return count
    
    # task 5
    def kth_level(self, k : int) -> int:
        levels = self.level_decomposition()
        if k >= len(levels):
            return 0
        return sum([self.nodes[id].volume for id in levels[k]])

    # task 6
    def k_paths(self, k : int) -> int:
        levels = self.level_decomposition()
        #print(levels)
        if len(levels) < k:
            return 0
        return sum([sum(self.nodes[id].volume for id in levels[i]) for i in range(min(k, len(levels)))])
    

    # ----------------------
    
    def summary(self, k: int):
        if self.capacity == -1:
            return []

        result = [0] * 6
        result[0] = self.k_children_volume(k)
        result[1] = self.k_size(k)
        result[2] = self.k_depth(k)
        result[3] = self.k_subtrees(k)
        result[4] = self.kth_level(k)
        result[5] = self.k_paths(k)
        return result