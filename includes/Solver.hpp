// IFNDEF !!!!!!!!

#include "Grid.hpp"

class Solver {
public:
    Solver(Grid* start_grid /*, void (*f) heuristic*/);
    virtual ~Solver();

    void explore();
    void solve();
    bool isFinal()

private:
    // heuristic        _heuristic;
    std::vector<Grid*>   _opened;
    std::vector<Grid*>   _closed;
    Grid*               _finalGrid;
    bool                _success;

}
