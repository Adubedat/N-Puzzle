
typedef struct Pos{
    int x;
    int y;
}              pos;

class Grid {

public:
    Grid(size_t size, int ......);
    virtual ~Grid();

    std::vector<Grid*>              expand();
    void                            setCost(const int cost);

private:
    Grid();
    pos                             _emptyPos;
    std::vector<std::vector<int> >  _matrix;
    // ???                          _hash;
    std::vector<Grid*>              _history;
    int                             _nbSteps;
    int                             _cost;
    // heuristic
}
