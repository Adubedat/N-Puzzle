#ifndef OPTIONS_HPP
# define OPTIONS_HPP

#include "Grid.hpp"
#include "Solver.hpp"

enum e_heuristic {
    mlc,
    man,
    ham
};

Grid*   getStartGrid(int const &argc, char** const &argv);
Solver* parseOptions(int const &argc, char** const &argv);

#endif
