#ifndef HAMMING_HPP
# define HAMMING_HPP

# include "IHeuristic.hpp"

class Hamming : public IHeuristic {
public:
    Hamming(const Grid* const goal);
    virtual int calculateAll(const Grid* const state) const;
    virtual int update(const Grid* const state, const pos swapped) const;
    virtual ~Hamming() = default;

private:
    Hamming() = default;

    const Grid* const   _goal;
};

#endif
