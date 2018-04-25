#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "GenerateGrid.hpp"
#include "Grid.hpp"
#include <deque>

typedef std::deque<Grid*>::iterator     deque_it;

class Solver {
public:
    Solver(Grid* start, IHeuristic* heuristic);
    virtual ~Solver();

    void        explore();
    void        solve();
    bool        isFinal(Grid*) const;
    void        display() const;

    void        insertSorted(Grid*, std::deque<Grid*> &);
    deque_it    find(const Grid* node, std::deque<Grid*>& set);

private:
    Solver() = default;


    IHeuristic*            _heuristic;
    Grid*                  _finalGrid;
    std::deque<Grid*>      _opened;
    std::deque<Grid*>      _closed;
    bool                   _success;

};
#endif
