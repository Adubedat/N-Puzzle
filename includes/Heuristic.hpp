#ifndef HEURISTIC_HPP
# define HEURISTIC_HPP

# define ABS(x) (x < 0 ? -x : x)

# include "Grid.hpp"

int manhattanDistance(Grid* const start, Grid* const goal);

#endif
