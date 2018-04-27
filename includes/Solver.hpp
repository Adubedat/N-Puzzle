#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "GenerateGrid.hpp"
#include "Grid.hpp"
#include <set>

typedef std::set<Grid*>::iterator     set_it;

struct compareGrid {
    bool operator() (const Grid* lhs, const Grid* rhs) const {
        if (lhs->getHash() == rhs->getHash())
            return (false);
        if (lhs->get_f_cost() == rhs->get_f_cost())
            return (lhs->getHash() < rhs->getHash());
        return ((lhs->get_f_cost() < rhs->get_f_cost()));
    }
};

class Solver {
public:
    Solver(Grid* start, Grid* goal, IHeuristic* heuristic);
    virtual ~Solver();

    void        solve();
    bool        isFinal(Grid*) const;
    void        display() const;

private:
    Solver() = default;
    // Grid*       getNextGridToExplore() const;
    // void        insertSorted(Grid*, std::deque<Grid*> &);
    // set_it      find(const Grid* node, std::deque<Grid*>& set);

    IHeuristic*                     _heuristic;
    Grid*                           _finalGrid;
    std::set<Grid*, compareGrid>    _opened;
    std::set<Grid*, compareGrid>    _closed;

};
#endif
