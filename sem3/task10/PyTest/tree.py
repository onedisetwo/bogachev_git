class TreeNode:
    data = []

    def __init__(self, smth):
        self.data = smth
    
    def __lt__(self, other):
        if len(self.data) == 0 and len(other.data) == 0:
            return False
        elif len(self.data) == 0:
            return True
        elif len(other.data) == 0:
            return False
        else:
            return self.data[0] < other.data[0] 
        
    def __eq__(self, other):
        return self.data == other.data
    
    def __str__(self):
        return str(self.data)
    
    def __len__(self):
        return len(self.data)

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
    nodes = []
    left_links = []
    right_links = []
    parent_links = []
    capacity = 0

    def __init__(self):
        self.nodes = [TreeNode([])]
        self.left_links = []
        self.right_links = []
        self.parent_links = []
        self.capacity = -1

    def factory_reset(self):
        self.nodes = [TreeNode([])]
        self.left_links = []
        self.right_links = []
        self.parent_links = []
        self.capacity = -1
    
    def add_node(self, new_value: TreeNode):
        new_index = self.capacity
        self.nodes[-1] = TreeNode(new_value)
        self.nodes += [TreeNode([])]
        self.left_links += [-1]
        self.right_links += [-1]
        self.parent_links += [-1]
        self.capacity += 1

        index = 0
        while index < new_index:
            if TreeNode(new_value) < self.nodes[index]:
                if self.left_links[index] == -1:
                    self.left_links[index] = new_index
                    self.parent_links[new_index] = index
                    break
                else:
                    index = self.left_links[index]
                    continue
            else:
                if self.right_links[index] == -1:
                    self.right_links[index] = new_index
                    self.parent_links[index] = index
                    break
                else:
                    index = self.right_links[index]
                    continue
        
            
    def read_from_file(self, file_name, count = 1):
        file = open(file_name, "r")
        data = file.readlines()
        file.close()

        self.capacity = 0
        for i in range(0, len(data), count):
            value = []
            for elem in data[i:i+count]:
                if len(elem.split()) != 2:
                    self.factory_reset()
                    return
                if not(elem.split()[1].lstrip("-").isdigit()):
                    self.factory_reset()
                    return
                #print(int(elem.split()[1]), correct_int(int(elem.split()[1])))
                value += [[elem.split()[0], correct_int(int(elem.split()[1]))]]
            
            self.add_node(value)

    def read_from_db(self, db):
        for elem in db:
            self.add_node(elem)

    # ------------------------

    def print_tree(self):
        self.print_subtree(0, 0, "r")
    
    def print_subtree(self, index, level, typ):
        if not(self.is_real(index)):
            return
        
        print ("  " * level + typ + ": ", end ="")
        print(self.nodes[index])
        self.print_subtree(self.left_links[index], level + 1, "l")
        self.print_subtree(self.right_links[index], level + 1, "r")

    # ------------------------
            
    def is_real(self, index):
        if index >= self.capacity:
            return False
        if self.nodes[index] == TreeNode([]):
            return False
        return True
    
    def size(self):
        count = 0
        for i in range(self.capacity):
            if self.nodes[i] != TreeNode([]):
                count += 1
        return count

    def children_count(self, index):
        count = 0
        if self.left_links[index] != -1:
            count += 1
        if self.right_links[index] != -1:
            count += 1
        return count
    
    # def vertex_children_counts(self) -> int:
    #     return [self.children_count[index] for index in range(self.capacity)]
    
    def subtrees_sizes(self):
        sizes = [0] * (self.capacity + 1)

        for i in range(self.capacity - 1, -1, -1):
            sizes[i] = len(self.nodes[i]) + \
                sizes[self.left_links[i]] + sizes[self.right_links[i]]

        return sizes[:self.capacity]
    
    def subtrees_depths(self):
        depths = [0] * (self.capacity + 1)

        for i in range(self.capacity - 1, -1, -1):
            depths[i] = len(self.nodes[i]) + \
                max(depths[self.left_links[i]], depths[self.right_links[i]])

        return depths[:self.capacity]
    
    def level_decomposition(self):
        levels = []

        if self.capacity == 0:
            return []

        levels = [[0]]
        level = 0
        while levels[level] != []:
            levels += [[]]
            for i in levels[level]:
                if self.left_links[i] != -1:
                    levels[level + 1].append(self.left_links[i])
                if self.right_links[i] != -1:
                    levels[level + 1].append(self.right_links[i])
            level += 1
            
        return levels[:-1]
    
    # def vertices_levels(self):
    #     level = [0] * self.capacity

    #     for index in range(self.capacity):
    #         for jndex in self.down_links[index]:
    #             level[jndex] = level[index] + 1

    #     return level 

    # def depth(self) -> int:
    #     return self.subtrees_depths()[0]
    
    # def max_level_size(self) -> int:
    #     if self.capacity == 0:
    #         return 0

    #     levels = self.level_decomposition()
    #     return max([len(level) for level in levels])
    
    # ----------------------

    # 1
    def count_leaves_lens(self):
        count = 0
        for i in range(self.capacity):
            if self.children_count(i) == 0:
                count += len(self.nodes[i])
        return count
    
    # 2
    def count_maximal_branch(self):
        if self.capacity == 0:
            return 0
        return self.subtrees_depths()[0]

    # 3
    def maximal_level(self):
        if self.capacity == 0:
            return 0

        levels = self.level_decomposition()
        sizes = []
        for level in levels:
            sizes.append(sum(len(self.nodes[i]) for i in level))
        return max(sizes)

    # 4
    def balance(self):
        if self.capacity == 0:
            return 0

        subtrees = self.subtrees_sizes()
        subtrees += [0]
        balances = [0] * self.capacity
        for i in range(self.capacity):
            balances[i] = abs(subtrees[self.left_links[i]] - subtrees[self.right_links[i]])
        return max(balances)

    # 5
    def count_with_one_child(self):
        count = 0
        for i in range(self.capacity):
            if self.children_count(i) == 1:
                count += len(self.nodes[i])
        return count

    
    def summary(self):
        if self.capacity == -1:
            return []

        result = [0] * 5
        result[0] = self.count_leaves_lens()
        result[1] = self.count_maximal_branch()
        result[2] = self.maximal_level()
        result[3] = self.balance()
        result[4] = self.count_with_one_child()
        return result