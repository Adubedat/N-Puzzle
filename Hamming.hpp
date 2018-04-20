#ifndef HAMMING_HPP
# define HAMMING_HPP

# include "IHeuristic.hpp"

class Hamming : public IHeuristic {
public:
    Hamming(const Grid* const goal);
    virtual int calculateAll(const Grid* const state);
    virtual int update(const Grid* const state, const pos swapped);

private:
    const Grid* const   _goal;

    virtual ~Hamming() = default;
};

#endif
