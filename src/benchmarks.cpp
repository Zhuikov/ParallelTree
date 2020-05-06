#include "BinaryTree.h"
#include "VectorGeneration.h"
#include "benchmark/benchmark.h"
#include <cmath>

static constexpr size_t start_tree_size = 16384;
static constexpr size_t end_tree_size   = 64 << 20;

int sum(int a, int b) { return a + b; }

double mul(double a, double b) { return sqrt(a * a + b * b); }

static void BM_Non_parallel(benchmark::State& state) {

    std::vector<double> vec = generate_vector<double>(state.range(0));
    BinaryTree<double> tree(vec);
    for (auto _ : state)
        tree.calculate(sum);
}
BENCHMARK(BM_Non_parallel)
    ->RangeMultiplier(4)->Range(start_tree_size, end_tree_size)
    ->Repetitions(50)->DisplayAggregatesOnly(true)->Unit(benchmark::kMillisecond);

static void BM_Parallel(benchmark::State& state) {

    std::vector<double> vec = generate_vector<double>(state.range(1));
    BinaryTree<double> tree(vec);
    for (auto _ : state)
        tree.calculate_parallel(sum, state.range(0));
}
BENCHMARK(BM_Parallel)
    ->RangeMultiplier(4)->Ranges({{2, 4}, {start_tree_size, end_tree_size}})
    ->Repetitions(50)->DisplayAggregatesOnly(true)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();


