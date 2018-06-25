#ifndef IHEURISTIC_HPP
# define IHEURISTIC_HPP

# include "Grid.hpp"

class Grid;
typedef struct Pos pos;

typedef enum Strategy { NONE, UC, GREEDY }  t_Strategy;

class IHeuristic{
public:
    virtual int calculateAll(const Grid* const state) const = 0;
    virtual int update(const Grid* const state, const pos swapped) const = 0;
    virtual t_Strategy get_strategy() const = 0;
};

#endif
