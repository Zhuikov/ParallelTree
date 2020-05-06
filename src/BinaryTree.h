#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <vector>
#include <functional>
#include <omp.h>

#include <iostream>

template<class T>
class BinaryTree
{
public:
    explicit BinaryTree(const std::vector<T> tree) :
        tree_array(tree) {}

    std::vector<T> calculate(std::function<T (T, T)> func) const {
        std::vector<T> res(tree_array.size());

        calc(0, tree_array, &res, func, tree_array.size());

        return res;
    }

    std::vector<T> calculate_parallel(std::function<T (T, T)> func, size_t thread_num) const {

        // <= 16 leaves
        if (tree_array.size() <= 31)
            return calculate(func);

        std::vector<T> res(tree_array.begin(), tree_array.begin() + 7);
        res.resize(tree_array.size());

        omp_set_num_threads(thread_num);
        #pragma omp parallel for schedule(static)
        for (size_t i = 7; i <= 14; i++) {
            calc(i, tree_array, &res, func, tree_array.size());
        }

        calc(0, res, &res, func, 15);

        return res;
    }

    ~BinaryTree() {}

private:
    std::vector<T> tree_array;

    /**
     * @brief calc -- tree traversal with function calculation
     * @param index -- start traversal index (root)
     * @param tree_array -- tree
     * @param calculated_tree -- result tree. Each node is task result
     * @param func -- two arguments task function
     * @param last_index -- last traversal index
     * @return func result for current node
     */
    T calc(size_t index, const std::vector<T> &tree_array,
           std::vector<T> *calculated_tree, std::function<T (T, T)> func, size_t last_index) const {
        T left_index  = get_left(index);
        T right_index = get_right(index);

        if (left_index >= last_index && right_index >= last_index) {
            (*calculated_tree)[index] = tree_array.at(index);
//            printf("Index %d -- leave. tree_array[%d] = %d\n", index, index, tree_array.at(index));
            return calculated_tree->at(index);
        }

        if (right_index >= last_index) {
            (*calculated_tree)[left_index] = tree_array.at(left_index);
            (*calculated_tree)[index] = func(tree_array.at(index), tree_array.at(left_index));
            return calculated_tree->at(index);
        }

        // impossible situation for complete binary tree
        if (left_index >= last_index) {
            (*calculated_tree)[right_index] = tree_array.at(right_index);
            (*calculated_tree)[index] = func(tree_array.at(index), tree_array.at(right_index));
            return calculated_tree->at(index);
        }


        T left_arg = calc(left_index, tree_array, calculated_tree, func, last_index);
        T right_arg = calc(right_index, tree_array, calculated_tree, func, last_index);
//        printf("now fun. Value = %d, left_arg = %d, right_arg = %d\n", tree_array.at(index), left_arg, right_arg);
        (*calculated_tree)[index] = func(tree_array.at(index), func(left_arg, right_arg));

        return calculated_tree->at(index);
    }

    inline size_t get_left(size_t index) const {
        return index * 2 + 1;
    }

    inline size_t get_right(size_t index) const {
        return index * 2 + 2;
    }

    inline size_t get_parent(size_t index) const {
        return (index - 1) / 2;
    }
};


#endif
