#ifndef _LIBGEN_VECTOR_HPP
#define _LIBGEN_VECTOR_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include "randomizer.hpp"

namespace libgen {

template<typename T, typename Randomizer = randomizer<T>>
class vector : public std::vector<T> {
public:
    template<typename Generator>
    void generate(int n, std::pair<T, T> const& range, Generator& gen) {
        Randomizer rng(range.first, range.second);

        this->resize(n);

        for (int i = 0; i < n; i++)
            (*this)[i] = rng(gen);
    }

    template<typename Generator>
    void permutation(int n, int b, Generator& gen) {
    	this->resize(n);
    	std::iota(this->begin(), this->end(), b);
    	std::shuffle(this->begin(), this->end(), gen);
    }

    friend std::ostream& operator<<(std::ostream& os, libgen::vector<T> const& V) {
        for(const T& x : V)
            os << x << ' ';
        return os;
    }
    
    void operator=(const std::vector<T>& v) {
        this->resize(v.size());
        for(std::size_t i = 0; i < v.size(); i++)
            (*this)[i] = v[i];
    }
private:
};

}

#endif
