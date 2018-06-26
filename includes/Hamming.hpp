#ifndef HAMMING_HPP
# define HAMMING_HPP

# include "IHeuristic.hpp"

class Hamming : public IHeuristic {

public:
    Hamming(const Grid* const goal, e_strategy strategy);
    virtual ~Hamming() = default;

    int         calculateAll(const Grid* const state) const;
    int         update(const Grid* const state, const pos swapped) const;
    e_strategy  get_strategy() const;

private:
    Hamming() = default;

    const Grid* const   _goal;
    e_strategy          _strategy;
};

#endif
