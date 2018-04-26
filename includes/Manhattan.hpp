#ifndef MANHATAN_HPP
# define MANHATAN_HPP

# define ABS(x) ((x < 0) ? -(x) : x)

# include "Grid.hpp"
# include "IHeuristic.hpp"

class Manhattan: public IHeuristic {
public:
    Manhattan(const Grid* const goal);
    ~Manhattan();
    int calculateAll(const Grid* const state) const;
    int update(const Grid* const state, const pos swapped) const;

protected:
    Manhattan();
    int     _manhattan_distance(pos state, pos goal) const;

    const Grid * const  _goal;
};

#endif
