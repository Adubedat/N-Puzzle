#include "Grid.hpp"

Grid::Grid(size_t size): _size(size), _matrix(size * size) {
    _nbSteps = 0;
    _cost = -1;
}

Grid::~Grid(){
    //TODO
}

std::vector<Grid*> Grid::expand() const{
    std::vector<Grid*> children;

    if (_emptyPos.x >= 0)
        children.push_back(_child({1,0}));
    // Todo


    return children;
}

void Grid::setCost(const int cost){
    _cost = cost;
}

int Grid::getCost() const{
    return _cost;
}

size_t  Grid::getSize() const{
    return this->_size;
}

// Swaps emptyPos with the neighboring tile located at distance dst
void Grid::swap(pos dst) {
    if ((_emptyPos + dst).x >= _size || (_emptyPos + dst).y >= _size)
        throw std::out_of_range("Trying to swap out of the grid.");
    (*this)[_emptyPos] = (*this)[_emptyPos + dst];
}

int& Grid::operator[](pos position){
    return _matrix[position.y * this->_size + position.x];
}

bool    Grid::operator==(Grid* rhs) const{
    return _matrix == rhs->_matrix;
}

Grid*   Grid::_child(pos emptyPos)const{
    Grid* clone = new Grid(this->_size);
    clone->_matrix = this->_matrix; //Possible?
    clone->_emptyPos = this->_emptyPos;
    clone->_history = this->_history;
    clone->_history.push_back(this);
    clone->_nbSteps = this->_nbSteps + 1;

    // Swap
    return clone;
}

pos     operator+(const pos& lhs, const pos&rhs){
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}
