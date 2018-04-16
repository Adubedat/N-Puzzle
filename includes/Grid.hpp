#ifndef GRID_HPP
# define GRID_HPP

#include <iostream>
#include <vector>

typedef struct Pos{
    int x;
    int y;
}              pos;

pos   operator+(const pos&, const pos&);

class Grid {

public:
    Grid(size_t size);
    virtual ~Grid();

    std::vector<Grid*>              expand() const;
    void                            setCost(const int cost);
    int                             getCost() const;
    size_t                          getSize() const;
    void                            swap(pos dst);

    int&                            operator[](pos);
    bool                            operator==(Grid* rhs) const;

private:
    Grid() = default;
    Grid*                           _child(pos emptyPos)const ;

    size_t                          _size;
    std::vector<int>                _matrix;
    pos                             _emptyPos;

    // ???                          _hash;
    std::vector<const Grid*>        _history;
    int                             _nbSteps;
    int                             _cost;

};

#endif
