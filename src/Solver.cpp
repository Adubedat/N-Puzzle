#include "Solver.hpp"


Solver::Solver(Grid* start, int (*heuristic)(Grid*, Grid*)):
_heuristic(heuristic), _success(false) {
    _opened.push_back(start);
    _finalGrid = _generateSolution(start->getSize());
    std::cout << start->toString() << std::endl;
    std::cout << "cost: " << heuristic(start, _finalGrid) << std::endl;
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

Grid*   Solver::_generateSolution(size_t size){
    std::vector<int>    matrix(size * size, 0);
    int                 len = matrix.size();
    int                 x = 0;
    int                 y = 0;
    int                 i = 1;

    while (i < len) {
        while (x < size && matrix[x + y * size] == 0 && i != len) {
            matrix[x++ + y * size] = i++;
        }
        x--;
        y++;
        while (y < size && matrix[x + y * size] == 0 && i != len)
            matrix[x + y++ * size] = i++;
        y--;
        x--;
        while (x >= 0 && matrix[x + y * size] == 0 && i != len)
            matrix[x-- + y * size] = i++;
        x++;
        y--;
        while (y >= 0 && matrix[x + y * size] == 0 && i != len)
            matrix[x + y-- * size] = i++;
        y++;
        x++;
    }
    return (new Grid(size, matrix));
}
