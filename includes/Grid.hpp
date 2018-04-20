#ifndef GRID_HPP
# define GRID_HPP

#include <iostream>
#include <vector>

typedef struct  Pos{
    int x;
    int y;
}               pos;

pos     operator+(const pos&, const pos&);

class Grid {

public:
    Grid(size_t size, std::vector<int> matrix);
    virtual ~Grid();

    std::vector<Grid*>              expand() const;
    void                            calculateCost(Grid*, int (*)(Grid*));
    bool                            isSolvable() const;

    int                             getCost() const;
    size_t                          getSize() const;
    Pos const                       searchPos(int) const;
    
    int&                            operator[](pos);
    bool                            operator==(Grid* rhs) const;

    std::string const               toString() const;

private:
    Grid() = default;
    Grid(const Grid*);

    void                            _swap(pos dst);
    Grid*                           _child(pos dst)const ;


    size_t                          _size;
    std::vector<int>                _matrix;
    pos                             _emptyPos;
    std::vector<const Grid*>        _history;
    int                             _nbSteps;
    int                             _cost;

};

#endif
