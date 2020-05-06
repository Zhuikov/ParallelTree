#include <iostream>
#include <chrono>
#include <cmath>

#include "benchmark/benchmark.h"

#include "BinaryTree.h"
#include "VectorGeneration.h"

int mai_n()
{
    std::vector<int> vec = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5
    };

    const size_t thread_num = 2;

    std::cout << "vec size = " << vec.size() << std::endl;
    BinaryTree<int> tree(vec);

    std::vector<int> calculated_tree  = tree.calculate([](int a, int b){return a + b;});
    std::vector<int> calculated_tree2 = tree.calculate_parallel([](int a, int b){return a + b;}, thread_num);

    for (auto v : calculated_tree)
        std::cout << v << " ";
    std::cout << std::endl;

    for (auto v : calculated_tree2)
        std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}

int main1()
{
    const size_t vec_size = 10000;
    std::vector<int> vec(vec_size);

    std::vector<int> ch_vec = generate_vector<int>(10);
    for (auto i : ch_vec)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "vec size = " << vec.size() << std::endl;
    BinaryTree<int> tree(vec);

//    std::chrono::time_point<std::chrono::system_clock>
//            start_non_parallel, end_non_parallel,
//            start_parallel, end_parallel;

//    start_non_parallel = std::chrono::system_clock::now();
//    std::vector<int> calculated_tree  = tree.calculate(sum);
//    end_non_parallel = std::chrono::system_clock::now();

//    const size_t thread_num = 2;
//    start_parallel = std::chrono::system_clock::now();
//    std::vector<int> calculated_tree2 = tree.calculate_parallel(sum, thread_num);
//    end_parallel = std::chrono::system_clock::now();

//    auto res_non_parallel = std::chrono::duration_cast<std::chrono::microseconds>
//            (end_non_parallel - start_non_parallel).count();
//    auto res_parallel = std::chrono::duration_cast<std::chrono::microseconds>
//            (end_parallel - start_parallel).count();

//    std::cerr << "Non parallel time: " << res_non_parallel << std::endl;
//    std::cerr << "Parallel time:     " << res_parallel     << std::endl;


    return 0;
}

int main2()
{
    #pragma omp parallel for
    for (int i = 0; i < 10; i++)
        std::cout << i << std::endl;

    return 0;
}
