#ifndef _LIBGEN_RANDOMIZER_HPP
#define _LIBGEN_RANDOMIZER_HPP

#include <type_traits>
#include <random>

namespace libgen {

template <typename T, typename Enable = void>
class randomizer;

template <typename T>
class randomizer<T, typename
    std::enable_if<std::is_floating_point<T>::value>::type> {
public:
    randomizer(T min, T max) : _rng(min, max) {  }

    template <typename Generator>
    T operator()(Generator& gen) {
        return _rng(gen);
    }

private:
    std::uniform_real_distribution<T> _rng;
};

template <typename T>
class randomizer<T, typename
    std::enable_if<std::is_integral<T>::value>::type> {
public:
    randomizer(T min, T max) : _rng(min, max) {  }

    template <typename Generator>
    T operator()(Generator& gen) {
        return _rng(gen);
    }

private:
    std::uniform_int_distribution<T> _rng;
};

}

#endif
