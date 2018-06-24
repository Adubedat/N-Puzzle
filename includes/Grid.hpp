#ifndef GRID_HPP
# define GRID_HPP

#include "IHeuristic.hpp"
#include <iostream>
#include <vector>
#include <string>

class IHeuristic;

typedef struct  Pos{
    int x;
    int y;
}               pos;

pos     operator+(const pos&, const pos&);
pos     operator-(const pos&, const pos&);

class Grid {

public:
    Grid(size_t size, std::vector<int> matrix);
    virtual ~Grid();

    std::vector<Grid*>              expand() const;
    void                            addHeuristic(IHeuristic*);
    bool                            isSolvable(const Grid* goal) const;

    std::size_t                     getHash() const;
    int                             get_f_cost() const;
    int                             get_g_cost() const;
    int                             get_h_cost() const;
    size_t                          getSize() const;
    Pos const                       searchPos(int) const;

    const int&                      operator[](pos) const;
    int&                            operator[](pos);
    bool                            operator==(const Grid& rhs) const;

    std::vector<const Grid*>        getGenealogy() const;
    std::string const               toString() const;

private:
    Grid() = default;
    Grid(const Grid*);

    std::size_t                     _hashFunction(std::vector<int> const &matrix) const;
    int                             _inversionNbr(const Grid* grid) const;
    Grid*                           _makeChild(pos dst)const ;
    void                            _swap(pos dst);

    const Grid*                     _parent;
    IHeuristic*                     _heuristic;
    std::size_t                     _size;
    std::vector<int>                _matrix;
    pos                             _emptyPos;
    std::vector<const Grid*>        _history;
    int                             _f_cost;
    int                             _g_cost;
    int                             _h_cost;
    std::size_t                     _hash;
};

#endif
