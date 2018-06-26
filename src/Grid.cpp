#include "Grid.hpp"

Grid::Grid(size_t size, std::vector<int> matrix):
    _parent(NULL),
    _size(size),
    _matrix(matrix),
    _hash(_hashFunction(matrix)) {

    _f_cost = -1;
    _g_cost = 0;
    _h_cost = -1;
    _emptyPos = searchPos(0);
    _parent = NULL;
}

Grid::Grid(const Grid* src){
    _heuristic = src->_heuristic;
    _size = src->_size;
    _matrix = src->_matrix;
    _emptyPos = src->_emptyPos;
    _g_cost = src->_g_cost;
    _h_cost = src->_h_cost;
    _f_cost = src->_f_cost;
    _hash = src->_hash;
    _parent = src;
}

Grid::~Grid(){
    _matrix.clear();
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
int             Grid::_inversionNbr(const Grid* grid) const {
    int     inversions = 0;
    int     len = (grid->_matrix).size();
    int     compared_value;

    for (int i = 0; i < len; i++) {
        compared_value = grid->_matrix[i];
        for (int j = i + 1; j < len; j++) {
            if (grid->_matrix[j] < compared_value && grid->_matrix[j] != 0)
                inversions++;
        }
    }
    return (inversions);
}

bool            Grid::isSolvable(const Grid* goal) const {
    int     startInversions = _inversionNbr(this);
    int     goalInversions = _inversionNbr(goal);

    // std::cout << startInversions << std::endl;
    // std::cout << goalInversions << std::endl;

    if (this->getSize() % 2 == 0) {
        startInversions += (this->getSize() - this->_emptyPos.y) % 2;
        goalInversions += (goal->getSize() - goal->_emptyPos.y) % 2;
    }
    return (startInversions % 2 == goalInversions % 2);
}


/*
**                  Getters and setters
*/

std::size_t     Grid::getHash() const {
    return (_hash);
}

int             Grid::get_f_cost() const {
    switch(this->_heuristic->get_strategy()){
        case NONE:      return this->_f_cost;
        case UC:        return this->_g_cost;
        case GREEDY:    return this->_h_cost;
    }
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

bool    Grid::operator==(const Grid& rhs) const {
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

// hashing vector function to identify grids faster
std::size_t     Grid::_hashFunction(std::vector<int> const &matrix) const {
  std::size_t seed = matrix.size();
  for(auto &elem : matrix) {
    seed ^= elem + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  return seed;
}

// Swaps emptyPos with the neighboring tile located at distance dst
void            Grid::_swap(pos dst) {
    (*this)[_emptyPos] = (*this)[_emptyPos + dst];
    (*this)[_emptyPos + dst] = 0;
    _emptyPos = _emptyPos + dst;
    // update hash with new matrix
    _hash = _hashFunction(this->_matrix);
}

Grid*           Grid::_makeChild(pos dst)const{
    Grid* child = new Grid(this);
    child->_g_cost += 1;
    child->_swap(dst);

    // child->_h_cost = _heuristic->update(child, child->_emptyPos - dst);
    child->_h_cost = _heuristic->calculateAll(child);

    child->_f_cost = child->_g_cost + child->_h_cost;
    child->_parent = this;
    // std::cout << child->toString() << std::endl;
    // std::cout << "g = " << child->get_g_cost() << " , h = " << child->get_h_cost() << ", f = " << child->get_f_cost() << std::endl;
    // std::cout << std::endl;
    return child;
}

std::vector<const Grid*>    Grid::getGenealogy() const{
    std::vector<const Grid*> genealogy;
    const Grid* current = this;

    while(current != NULL){
        genealogy.insert(genealogy.begin(), current);
        current = current->_parent;
    }
    return genealogy;
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
