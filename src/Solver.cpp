#include "Solver.hpp"


Solver::Solver(Grid* start, int (*heuristic)(Grid*)):
_heuristic(heuristic), _success(false) {
    _opened.push_back(start);
    _finalGrid = _generateSolution(start->getSize());
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
    // TODO



}

void    Solver::calculateCost(Grid* grid){
    // Todo
    int cost = 0;
    grid->setCost(cost);
}

bool Solver::compareCosts(const Grid* a, const Grid* b){
    if (a->getCost() < b->getCost())
        return true;
    else
        return false;
}


bool    Solver::isFinal(Grid* grid) const{
    return grid == _finalGrid;
}

void    Solver::display() const{
    // Display solution
    // TODO
}

Grid*   Solver::_generateSolution(size_t size){
    Grid* solution = new Grid(size);
    // TODO


    return solution;
}
