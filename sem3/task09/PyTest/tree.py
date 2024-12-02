class Tree:
    nodes = []
    down_links = []
    up_links = []
    capacity = 0

    def __init__(self):
        self.nodes = []
        self.down_links = []
        self.up_links  = []
        self.capacity = 0
    
    def add_node(self, new_value):
        new_index = len(self.nodes)
        self.nodes += [new_value]
        self.capacity += 1
        index = 0

        self.down_links += [[]]
        self.up_links += [0]

        while index < new_index:
            if self.down_links[index] == []:
                self.down_links[index].append(new_index)
                self.up_links[new_index] = index
                break
            if new_value < self.nodes[index]:
                if self.nodes[self.down_links[index][0]] < self.nodes[index]:
                    index = self.down_links[index][0]
                    continue
                else:
                    self.down_links[index] = [new_index] + self.down_links[index]
            elif new_value == self.nodes[index]:
                if len(self.down_links[index]) > 1:
                    self.down_links[index].insert(1, new_index)
                elif self.nodes[self.down_links[index][0]] < self.nodes[index]:
                    self.down_links[index] += [new_index]
                else:
                    self.down_links[index] = [new_index] + self.down_links[index]
            else:
                if self.nodes[self.down_links[index][-1]] > self.nodes[index]:
                    index = self.down_links[index][-1]
                    continue
                else:
                    self.down_links[index].append(new_index)

            self.up_links[new_index] = index
            break
        
            
    def read_from_file(self, file_name):
        file = open(file_name, "r")
        data = file.readlines()
        file.close()

        for elem in data:
            value = [elem.split()[0], int(elem.split()[1])]
            self.add_node(value)

    def read_from_db(self, db):
        for elem in db:
            self.add_node(elem)

    def read_from_lines(self, lines):
        if len(lines) == 0:
            return

        poses = [0] * len(lines)
        self.add_node([lines[0].split()[0], int(lines[0].split()[1])])
        for i in range(1, len(lines)):
            level = (lines[i].count(" ") - 1) // 2
            for j in range(i - 1, -1, -1):
                if (lines[j].count(" ") - 1) // 2 <= level:
                    break
            if (lines[j].count(" ") - 1) // 2 == level:
                poses[i] = poses[j] + 1 
            else:
                poses[i] = poses[j] * 2 + 1
            if poses[i] >= self.capacity:
                self.nodes += [[] for i in range(self.capacity + 1)]
                self.capacity = 2 * self.capacity + 1
            self.nodes[poses[i]] = [lines[i].split()[0], int(lines[i].split()[1])]

    # ------------------------

    def print_tree(self):
        self.print_subtree(0, 0)
    
    def print_subtree(self, index, level):
        if not(self.is_real(index)):
            return
        
        print ("  " * level, end ="")
        print(self.nodes[index])
        for i in self.down_links[index]:
            self.print_subtree(i, level + 1)
        


    # ------------------------
            
    def is_real(self, index):
        if index >= len(self.nodes):
            return False
        if self.nodes[index] == []:
            return False
        return True
    
    def size(self):
        count = 0
        for i in range(len(self.nodes)):
            if self.nodes[i] != []:
                count += 1
        return count

    def children_count(self, index):
        return len(self.down_links[index])
    
    def vertex_children_counts(self) -> int:
        return [len(self.down_links[index]) for index in range(self.capacity)]
    
    def subtrees_sizes(self):
        sizes = [0] * self.capacity

        for i in range(self.capacity - 1, -1, -1):
            for index in self.down_links[i]:
                sizes[i] += sizes[index]
            sizes[i] += 1

        return sizes
    
    def subtrees_depths(self):
        depths = [1] * self.capacity

        for i in range(self.capacity - 1, -1, -1):
            for index in self.down_links[i]:
                depths[i] = max(depths[i], depths[index] + 1)

        return depths
    
    def level_decomposition(self):
        levels = []

        if self.capacity == 0:
            return []

        levels = [[0]]
        level = 0
        while levels[level] != []:
            levels += [[]]
            for i in levels[level]:
                levels[level + 1].extend(self.down_links[i])
            level += 1
            
        return levels[:-1]
    
    def vertices_levels(self):
        level = [0] * self.capacity

        for index in range(self.capacity):
            for jndex in self.down_links[index]:
                level[jndex] = level[index] + 1

        return level 

    def depth(self) -> int:
        return self.subtrees_depths()[0]
    
    def max_level_size(self) -> int:
        if self.capacity == 0:
            return 0

        levels = self.level_decomposition()
        return max([len(level) for level in levels])
    
    # ----------------------

    # 1
    def count_with_k_children(self, k: int) -> int:
        children = self.vertex_children_counts()
        return children.count(k)
    
    # 2
    def count_with_k_vertices(self, k: int) -> int:
        sizes = self.subtrees_sizes()

        count = 0
        for s in sizes:
            if s <= k:
                count += 1
        return count

    # 3
    def count_small_trees(self, k: int) -> int:
        depths = self.subtrees_depths()

        count = 0
        for d in depths:
            if d <= k:
                count += 1
        return count

    # 4
    def count_very_small_trees(self, k: int) -> int:
        levels_sizes = [[] for i in range(self.capacity)]

        for i in range(self.capacity - 1, -1, -1):
            levels_sizes[i] = [1]
            for index in self.down_links[i]:
                for _ in range(0, len(levels_sizes[index]) + 1 - len(levels_sizes[i])):
                    levels_sizes[i] += [0]
                for j in range(len(levels_sizes[index])):
                    levels_sizes[i][j + 1] += levels_sizes[index][j]

        count = 0
        for i in range(self.capacity):
            if max(levels_sizes[i]) <= k:
                count += 1
        
        return count
    # 5
    def count_in_level(self, k: int) -> int:
        levels =  self.level_decomposition()
        if k < 0 or k >= len(levels):
            return 0
        return len(levels[k])
    
    # 6
    def count_in_long_branches(self, k: int) -> int:
        depths = self.subtrees_depths()
        level = self.vertices_levels()

        count = 0
        for i in range(self.capacity):
            if level[i] + depths[i] >= k:
                count += 1
        return count
    
    def summary(self, k: int):
        result = [0] * 6
        result[0] = self.count_with_k_children(k)
        result[1] = self.count_with_k_vertices(k)
        result[2] = self.count_small_trees(k)
        result[3] = self.count_very_small_trees(k)
        result[4] = self.count_in_level(k)
        result[5] = self.count_in_long_branches(k)
        return result
