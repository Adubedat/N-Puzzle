#ifndef IHEURISTIC_HPP
# define IHEURISTIC_HPP

# include "Grid.hpp"

class Grid;
typedef struct Pos pos;

enum e_strategy { NONE, UC, GREEDY };

class IHeuristic{
public:
    virtual ~IHeuristic() = 0;
    virtual int calculateAll(const Grid* const state) const = 0;
    virtual int update(const Grid* const state, const pos swapped) const = 0;
    virtual e_strategy get_strategy() const = 0;
};

#endif
