#include "Solver.hpp"


Solver::Solver(Grid* start, IHeuristic* heuristic):
_heuristic(heuristic), _success(false) {
    _opened.push_back(start);
    _finalGrid = generateSolution(start->getSize());
    std::cout << start->toString() << std::endl;
}

Solver::~Solver(){
    // TODO
}

void Solver::explore() {
    Grid* target;

    // selectionner la grille de plus faible cout parmi opened
    // target = min...
    // la mettre dans _closed

    // Obtenir les 4 grilles voisines
    std::vector<Grid *> neighbors = target->expand();

    // Evaluer les 4 grilles voisines
        // Calculer leur cout
        // Comparer
        //
    // TODO
}

void Solver::solve() {
    Grid* state;
    std::vector<Grid*> children;

    while (!_opened.empty() && !_success){
        state = _opened.front();
        if (*state == *_finalGrid)
            _success = true;
        else {
            _opened.pop_front();
            _closed.push_back(state);
            children = state->expand();
            // remove those already visited
            for(Grid* child : children)
                _opened.push_back(child);
            // Finish algorithm
        }
        // if (_opened.size() >= 30)
        //     _success = true;
    }

    std::cout << _finalGrid->toString() << std::endl;

}

// bool Solver::compareCosts(const Grid* a, const Grid* b){
//     if (a->getCost() < b->getCost())
//         return true;
//     else
//         return false;
// }


bool    Solver::isFinal(Grid* grid) const{
    return grid == _finalGrid;
}

void    Solver::display() const{
    // Display solution
    // TODO
}
