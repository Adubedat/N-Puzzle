#include "Grid.hpp"

Grid::Grid(size_t size, std::vector<int> matrix):
    _size(size),
    _matrix(matrix) {

    _f_cost = -1;
    _g_cost = 0;
    _h_cost = -1;
    _emptyPos = searchPos(0);
}

Grid::Grid(const Grid* src){
    _heuristic = src->_heuristic;
    _size = src->_size;
    _matrix = src->_matrix;
    _emptyPos = src->_emptyPos;
    _history = src->_history;
    _g_cost = src->_g_cost;
    _h_cost = src->_h_cost;
}

Grid::~Grid(){
}

std::vector<Grid*> Grid::expand() const{
    std::vector<Grid*> children;

    if (_emptyPos.x > 0)
        children.push_back(_makeChild({-1,0}));
    if (_emptyPos.x < _size - 1)
        children.push_back(_makeChild({1,0}));
    if (_emptyPos.y > 0)
        children.push_back(_makeChild({0,-1}));
    if (_emptyPos.y < _size - 1)
        children.push_back(_makeChild({0,1}));
    return children;
}

void            Grid::addHeuristic(IHeuristic* heuristic){
    this->_heuristic = heuristic;
    this->_h_cost = heuristic->calculateAll(this);
    this->_f_cost = _g_cost + _h_cost;
}

/*
**      If the grid width is odd, then the number of inversions in a solvable situation is even.
**      If the grid width is even, and the blank is on an even row counting from the bottom (second-last, fourth-last etc), then the number of inversions in a solvable situation is odd.
**      If the grid width is even, and the blank is on an odd row counting from the bottom (last, third-last, fifth-last etc) then the number of inversions in a solvable situation is even.
*/

bool            Grid::isSolvable() const {
    int     inversions = 0;
    int     len = _matrix.size();
    int     compared_value;
    bool    onOddRowFromBottom;

    for (int i = 0; i < len; i++) {
        compared_value = _matrix[i];
        for (int j = i + 1; j < len; j++) {
            if (_matrix[j] < compared_value && _matrix[j] != 0)
                inversions++;
        }
    }
    if ((_size - _emptyPos.y) % 2 == 1)
        onOddRowFromBottom = true;
    else
        onOddRowFromBottom = false;
    if ((_size % 2 == 1 && inversions % 2 == 0)
        || ((_size % 2 == 0) && (onOddRowFromBottom == (inversions % 2 == 0))))
        return (true);
    else
        return (false);
}


/*
**                  Getters and setters
*/

int             Grid::get_f_cost() const {
    return this->_g_cost + this->_h_cost;
}

int             Grid::get_g_cost() const {
    return this->_g_cost;
}
int             Grid::get_h_cost() const {
    return this->_h_cost;
}

size_t          Grid::getSize() const{
    return this->_size;
}



const int&        Grid::operator[](pos position) const{
    if (position.x < 0 || position.x >= _size || position.y < 0 || position.y >= _size)
        throw std::out_of_range("Trying to access an element out of the grid.");
    return _matrix[position.y * this->_size + position.x];
}

int&               Grid::operator[](pos position){
    if (position.x < 0 || position.x >= _size || position.y < 0 || position.y >= _size)
        throw std::out_of_range("Trying to access an element out of the grid.");
    return _matrix[position.y * this->_size + position.x];
}

bool    Grid::operator==(Grid& rhs) const{
    return _matrix == rhs._matrix;
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

/*
**              Private functions
*/

// Swaps emptyPos with the neighboring tile located at distance dst
void            Grid::_swap(pos dst) {
    (*this)[_emptyPos] = (*this)[_emptyPos + dst];
    (*this)[_emptyPos + dst] = 0;
    _emptyPos = _emptyPos + dst;
}

Grid*           Grid::_makeChild(pos dst)const{
    Grid* child = new Grid(this);
    child->_history.push_back(this);
    child->_g_cost += 1;
    child->_swap(dst);
    child->_h_cost = _heuristic->update(child, child->_emptyPos - dst);
    child->_f_cost = child->_g_cost + child->_h_cost;
    return child;
}

Pos const       Grid::searchPos(int number) const {

    struct Pos  emptyPos;

    for (std::vector<int>::const_iterator it = _matrix.begin(); it != _matrix.end(); it++) {

        if (*it == number) {
            emptyPos.x = (it - _matrix.begin()) % _size;
            emptyPos.y = (it - _matrix.begin()) / _size;
        }
    }
    return (emptyPos);
}

pos             operator+(const pos& lhs, const pos&rhs){
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

pos             operator-(const pos& lhs, const pos&rhs){
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}
