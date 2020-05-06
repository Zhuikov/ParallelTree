#include <random>
#include <algorithm>
#include <typeinfo>

template<class T>
using uniform_distribution =
typename std::conditional<
    std::is_floating_point<T>::value,
    std::uniform_real_distribution<T>,
    typename std::conditional<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        void
    >::type
>::type;

template<typename T>
std::vector<T> generate_vector(size_t size)
{
    static_assert (std::is_integral<T>::value || std::is_floating_point<T>::value,
                   "Illegal type for vector type");

    std::vector<T> res(size);
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{rnd_device()};
    uniform_distribution<T> distr {1, 10};

    std::generate(res.begin(), res.end(),
                  [&distr, &mersenne_engine]() {
        return distr(mersenne_engine);
    });

    return res;
}
