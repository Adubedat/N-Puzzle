#include "Grid.hpp"

/*Grid::Grid(size, heuristic){

    calculateCost(heuristic);
}*/

Grid::Grid(size_t const &size, std::vector<int> &matrix, int const &cost) :
    _size(size),
    _matrix(matrix),
    _nbSteps(0),
    _cost(cost),
    _emptyPos(searchEmptyPos())
{
}

Pos const                   Grid::searchEmptyPos() const {

    struct Pos  emptyPos;

    for (std::vector<int>::const_iterator it = _matrix.begin(); it != _matrix.end(); it++) {

        if (*it == 0) {
            emptyPos.x = (it - _matrix.begin()) % _size;
            emptyPos.y = (it - _matrix.begin()) / _size;
        }
    }
    return (emptyPos);
}

std::string const           Grid::toString() const {

    std::string str;

    for (int i = 0; i < _matrix.size(); i++) {
        if (i % _size == 0 && i != 0)
            str += "\n";
        else if (i != 0)
            str += " | ";
        str += std::to_string(_matrix.at(i));
        if (_matrix.at(i) < 10)
            str += " ";
    }

    return (str);
}

/*std::vector<Grid*> Grid::expand(){
    // generer vecteur de possibilites
    //neighbors = ...

    //return neighbors;
}

void Grid::setCost(const int cost){
    _cost = cost;
}*/
