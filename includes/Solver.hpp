#ifndef SOLVER_HPP
# define SOLVER_HPP

#include "Grid.hpp"
#include <set>

typedef std::multiset<Grid*>::iterator     set_it;

struct compareHash {
    bool operator() (const Grid* lhs, const Grid* rhs) const {
        return (lhs->getHash() < rhs->getHash());
    }
};

struct compareCost {
    bool operator() (const Grid* lhs, const Grid* rhs) const {
        return (lhs->get_f_cost() < rhs->get_f_cost());
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

    IHeuristic*                         _heuristic;
    Grid*                               _finalGrid;
    Grid*                               _result;
    std::multiset<Grid*, compareCost>   _opened;
    std::set<Grid*, compareHash>        _closed;
    int                                 _total_selected;
    int                                 _total_represented;
};

#endif
