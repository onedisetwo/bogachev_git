class Tree:
    nodes = []
    capacity = 0

    def __init__(self):
        self.nodes = []
        self.capacity = 0
    
    def add_node(self, new_value):
        index = 0

        if self.capacity == 0:
            self.nodes = [new_value]
            self.capacity = 1
            return
        
        while index < self.capacity and self.nodes[index] != []:
            if new_value < self.nodes[index]:
                index = index * 2 + 1
            else:
                index = index * 2 + 2

        if index >= self.capacity:
            self.nodes += [[] for i in range(self.capacity + 1)]
            self.capacity = 2 * self.capacity + 1
        self.nodes[index] = new_value
        
            
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
        if index == 0:
            print("u: ", end="")
        elif index % 2 == 1:
            print("l: ", end="")
        else:
            print("r: ", end="")
        print(self.nodes[index])
        self.print_subtree(index * 2 + 1, level + 1)
        self.print_subtree(index * 2 + 2, level + 1)
        


    # ------------------------
            
    def is_real(self, index):
        if index >= self.capacity:
            return False
        if self.nodes[index] == []:
            return False
        return True
    
    def size(self):
        count = 0
        for i in range(self.capacity):
            if self.is_real(i):
                count += 1
        return count

    def children_count(self, index):
        count = 0
        if index * 2 + 1 >= self.capacity:
            return 0
        if self.is_real(index * 2 + 1):
            count += 1
        if index * 2 + 2 >= self.capacity:
            return count
        if self.is_real(index * 2 + 2):
            count += 1
        return count
    
    def count_vertex_types(self) -> int:
        count_0 = 0
        count_1 = 0
        count_2 = 0
        children = 0

        for i in range(self.capacity):
            if self.is_real(i):
                children = self.children_count(i)
                if children == 0:
                    count_0 += 1
                elif children == 1:
                    count_1 += 1
                elif children == 2:
                    count_2 += 1
        
        return [count_0, count_1, count_2]
    
    def subtrees_depths(self):
        depths = [0] * self.capacity

        for i in range(self.capacity - 1, -1, -1):
            if self.is_real(i):
                if self.is_real(i * 2 + 1):
                    depths[i] = depths[i * 2 + 1]
                if self.is_real(i * 2 + 2):
                    depths[i] = max(depths[i], depths[i * 2 + 2])        
                depths[i] += 1
            
        return depths
    
    def level_decomposition(self):
        levels = []
        index = 0
        level = 0
        stop = 1

        #print(self.nodes)
        while stop <= self.capacity:
            levels += [[]]
            while index < stop:
                if self.is_real(index):
                    levels[level].append(self.nodes[index])
                index += 1
            stop = 2 * stop + 1
            level += 1
        
        return levels

    def depth(self) -> int:
        return self.subtrees_depths()[0]
    
    def max_level_size(self) -> int:
        if self.capacity == 0:
            return 0

        levels = self.level_decomposition()
        return max([len(level) for level in levels])
    
    def depths_difference(self) -> int:
        maximum = 0
        depths = self.subtrees_depths()

        for i in range((self.capacity - 1) // 2):
            diff = abs(depths[i * 2 + 1] - depths[i * 2 + 2])
            maximum = max(maximum, diff)
        
        return maximum
    
    def characteristics_list(self):
        T = self.size()
        [L, C1, C2] = self.count_vertex_types()
        H = len(self.level_decomposition())
        #print(self.level_decomposition())
        W = self.max_level_size()
        B = self.depths_difference()

        return [T, L, C1, C2, H, W, B]
    
    # ------------------------------

    def swap(self, i1, i2):
        if i1 >= self.capacity or i2 >= self.capacity:
            return
        self.nodes[i1], self.nodes[i2] = self.nodes[i2], self.nodes[i1]

    def set_of_nodes(self):
        this_set = set()
        for i in range(self.capacity):
            if self.is_real(i):
                this_set.add(tuple(self.nodes[i]))
        return this_set

    def __eq__(self, other):
        if self.size() != other.size():
            return False

        cap = min(self.capacity, other.capacity)
        for i in range(cap):
            if self.nodes[i] != other.nodes[i]:
                return False
            
        return True

    def have_same_elements(self, other):
        return self.set_of_nodes() == other.set_of_nodes()

    # ---------------------------------

    # task 1
    def heap_check(self):
        for i in range((self.capacity - 1) // 2):
            if not(self.is_real(i)):
                continue
            if self.is_real(i * 2 + 1) and self.nodes[i] < self.nodes[i * 2 + 1]:
                return False
            if self.is_real(i * 2 + 2) and self.nodes[i] < self.nodes[i * 2 + 2]:
                return False
        return True
    
    # task 2
    def level_check(self):
        levels = self.level_decomposition()
        for i in range(len(levels)):
            level = levels[i]
            for j in range(len(level) - 1):
                if level[j][1] > level[j + 1][1]:
                    return False

        return True
    
    # task 3
    def all_left_rotates(self):
        for i in range(self.capacity):
            self.left_rotate_at(i)
    
    # task 4
    def all_right_rotates(self):
        for i in range(self.capacity):
            self.right_rotate_at(i)
    
    def left_rotate_at(self, index):
        if not(self.is_real(index)):
            return
        if self.is_real(index * 2 + 1):
            return

        jndex = index * 2 + 2
        if not(self.is_real(jndex) and self.is_real(jndex * 2 + 1)):
            return
        
        while self.is_real(jndex * 2 + 1):
            jndex = jndex * 2 + 1
        
        if self.is_real(jndex * 2 + 2):
            return

        self.swap(index, index * 2 + 1)
        self.swap(index, jndex)               
    
    def right_rotate_at(self, index):
        if not(self.is_real(index)):
            return
        if self.is_real(index * 2 + 2):
            return

        jndex = index * 2 + 1
        if not(self.is_real(jndex) and self.is_real(jndex * 2 + 2)):
            return
        
        while self.is_real(jndex * 2 + 2):
            jndex = jndex * 2 + 2
        
        if self.is_real(jndex * 2 + 1):
            return

        self.swap(index, index * 2 + 2)
        self.swap(index, jndex)

    # -----------------------------

    def delete_subtree(self, index):
        if not(self.is_real(index)):
            return

        self.nodes[index] = []
        for i in range(index * 2 + 1, self.capacity):
            if not(self.is_real((i - 1) // 2)):
                self.nodes[i] = []
    
    # task 5
    def delete_subtrees(self, string, k):
        candidates = [True] * self.capacity
        for i in range(self.capacity - 1, -1, -1):
            if self.is_real(i):
                if not(string in self.nodes[i][0]):
                    candidates[i] = False
                elif i * 2 + 1 < self.capacity and not(candidates[i * 2 + 1]):
                    candidates[i] = False
                elif i * 2 + 2 < self.capacity and not(candidates[i * 2 + 2]):
                    candidates[i] = False  

        depths = self.subtrees_depths()
        for i in range(self.capacity):
            if depths[i] >= k and candidates[i]:
                self.delete_subtree(i)
    
    # task 6
    def delete_subtrees_with_branches(self, string, k):
        candidates = [True] * self.capacity
        branches = [0] * self.capacity

        for i in range(self.capacity - 1, -1, -1):
            if self.is_real(i):
                if not(string in self.nodes[i][0]):
                    candidates[i] = False
                    continue
                
                l_status = True
                r_status = True
                if i * 2 + 1 < self.capacity:
                    if candidates[i * 2 + 1]:
                        branches[i] = branches[i * 2 + 1]    
                    else:
                        l_status = False 
                if i * 2 + 2 < self.capacity:
                    if candidates[i * 2 + 2]:
                        branches[i] = max(branches[i], branches[i * 2 + 2])
                    else:
                        r_status = False
                
                if not(l_status) and not(r_status):
                    candidates[i] = False
                branches[i] += 1

        for i in range(self.capacity):
            if branches[i] >= k and candidates[i]:
                self.delete_subtree(i)
    
    # task 7
    def delete_under_bad_level(self, string, k):
        levels = self.level_decomposition()
        count = 0
        max_count = 0

        for i in range(len(levels)):
            count = 0
            max_count = -1
            for elem in levels[i]:
                if string in elem[0]:
                    count += 1
                    if count > max_count:
                        max_count = count
                else:
                    count = 0
            if max_count >= k:
                #print(f"level: {i}")
                self.delete_under_level(i)
                break
    
    def delete_under_level(self, level):
        start = 0
        for _ in range(level):
            start = start * 2 + 1
        
        for i in range(start, self.capacity):
            self.nodes[i] = []
