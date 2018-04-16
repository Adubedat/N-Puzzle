#ifndef GRID_HPP
# define GRID_HPP

#include <iostream>
#include <vector>

typedef struct  Pos{
    int x;
    int y;
}               pos;

pos   operator+(const pos&, const pos&);

class Grid {

public:
    Grid(size_t size, std::vector<int> matrix);
    virtual ~Grid();

    std::vector<Grid*>              expand() const;
    int                             getCost() const;
    void                            calculateCost(Grid*, int (*)(Grid*));
    size_t                          getSize() const;
    void                            swap(pos dst);
    std::string const               toString() const;

    int&                            operator[](pos);
    bool                            operator==(Grid* rhs) const;

private:
    Grid() = default;
    Grid(const Grid*);
    Grid*                           _child(pos dst)const ;
    Pos const                       _searchEmptyPos() const;

    size_t                          _size;
    std::vector<int>                _matrix;
    pos                             _emptyPos;
    // ???                          _hash;
    std::vector<const Grid*>        _history;
    int                             _nbSteps;
    int                             _cost;

};

#endif
