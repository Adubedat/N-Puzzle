# include <iostream>
# include <vector>

struct Pos{
    int x;
    int y;
};

class Grid {

public:

    Grid(size_t const &size, std::vector<int> &matrix, int const &cost);
    virtual ~Grid() = default;

    //std::vector<Grid*>            expand();
    //void                          setCost(const int cost);

    std::string const               toString() const;


private:

    Grid() = default;

    Pos const                       searchEmptyPos() const;

    size_t const                    _size;
    Pos const                       _emptyPos;
    std::vector<int>                _matrix;
    // ???                          _hash;
    std::vector<Grid*>              _history;
    int const                       _nbSteps;
    int const                       _cost;
    // heuristic
};
