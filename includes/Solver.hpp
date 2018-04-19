#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "Grid.hpp"

class Solver {
public:
    Solver(Grid* start, int (*heuristic)(Grid*, Grid*));
    virtual ~Solver();

    void        explore();
    void        solve();
    // static bool compareCosts(const Grid*, const Grid*);
    bool        isFinal(Grid*) const;
    void        display() const;


private:
    Solver() = default;
    Grid*       _generateSolution(size_t size);

    int                 (*_heuristic)(Grid*, Grid*);
    Grid*               _finalGrid;
    std::vector<Grid*>  _opened;
    std::vector<Grid*>  _closed;
    bool                _success;

};
#endif
