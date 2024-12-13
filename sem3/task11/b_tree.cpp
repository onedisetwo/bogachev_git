# include "b_tree.h"

template class b_tree<student>;

template<class T>
int b_tree<T>::count_k_size (b_tree_node<T> *curr, int k) const {
	int res = 0, child_count;
	if(curr == nullptr)
		return 0;
	child_count = curr->count_children();
	if(child_count == k)
		res += curr->get_size();
	for(int i = 0; i < child_count; i++)
		res += count_k_size(curr->children[i], k);
	return res;
}

template<class T>
int b_tree<T>::count_vertices_in_subtree (b_tree_node<T> *curr, int k, int *total) const {
	int num;
	if(curr == nullptr)
		return 0;
	num = 1;
	for(int i = 0; i <= curr->size; i++){
		num += count_vertices_in_subtree(curr->children[i], k, total);
	}
	if(num <= k)
		*total += curr->get_size();
	return num;
}

template<class T>
int b_tree<T>::count_levels_in_subtree (b_tree_node<T> *curr, int k, int *total) const {
	int child_depth, max_depth = -1;
	if(curr == nullptr)
		return 0;
	for(int i = 0; i <= curr->size; i++){
		child_depth = count_levels_in_subtree(curr->children[i], k, total);
		max_depth = std::max(max_depth, child_depth);
	}
	if(max_depth + 1 <= k)
		*total += curr->get_size();
	return max_depth + 1;
}

/*template<class T>
int b_tree<T>::get_count_total (b_tree_node<T> *curr) const {
	int total = 0;
	if(curr == nullptr)
		return 0;
	for(int i = 0; i <= curr->size; i++)
		total += get_count_total(curr->children[i]);
	return total + curr->get_size();
}*/

template<class T>
int b_tree<T>::count_vertices_on_level (b_tree_node<T> *curr, int level, int curr_level, int *level_size) const {
	int total = 0;
	if(curr == nullptr)
		return 0;
	if(level == curr_level){
		*level_size += curr->get_size();
		return 1;
	}
	for(int i = 0; i <= curr->size; i++)
		total += count_vertices_on_level(curr->children[i], level, curr_level + 1, level_size);
	return total;
}

template<class T>
int b_tree<T>::get_count_tiny_subtrees (b_tree_node<T> *curr, int k) const {
    int curr_width = 0, total = 0;
    if (curr == nullptr)
        return 0;
    for(int curr_level = 1; curr_width <= k; curr_level++) {
        curr_width = count_vertices_on_level(curr, curr_level, 1, &total);
        if(curr_width == 0)
            break;
    }
    if(curr_width <= k)
		return total;
	total = 0;
	for(int i = 0; i <= curr->size; i++)
		total += get_count_tiny_subtrees(curr->children[i], k);
	return total;
}

template<class T>
int b_tree<T>::count_sizes_on_level (b_tree_node<T> *curr, int level, int curr_level) const {
	int total = 0;
	if(curr == nullptr)
		return 0;
	if(level == curr_level)
		return curr->get_size();
	for(int i = 0; i <= curr->size; i++)
		total += count_sizes_on_level(curr->children[i], level, curr_level + 1);
	return total;
}

template<class T>
int b_tree<T>::count_sizes_on_k_branches (b_tree_node<T> *curr, int k, int curr_level) const {
	int total = 0, tmp;
	if(curr == nullptr)
		return 0;
	if(k == curr_level)
		return curr->get_size();
	for(int i = 0; i <= curr->size; i++) {
		tmp = count_sizes_on_k_branches(curr->children[i], k, curr_level + 1);
		if(total == 0 && tmp > 0)
			total += curr->get_size();
		total += tmp;
	}
	return total;
}
