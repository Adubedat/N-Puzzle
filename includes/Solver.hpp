#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "GenerateGrid.hpp"
#include "Grid.hpp"
#include <deque>

class Solver {
public:
    Solver(Grid* start, IHeuristic* heuristic);
    virtual ~Solver();

    void        explore();
    void        solve();
    bool        isFinal(Grid*) const;
    void        display() const;

    static bool compareCosts(const Grid*, const Grid*);

private:
    Solver() = default;


    IHeuristic*            _heuristic;
    Grid*                  _finalGrid;
    std::deque<Grid*>      _opened;
    std::deque<Grid*>      _closed;
    bool                   _success;

};
#endif
