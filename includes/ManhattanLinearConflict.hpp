#ifndef MANHATAN_LINEAR_CONFLICT_HPP
# define MANHATAN_LINEAR_CONFLICT_HPP

# include "Manhattan.hpp"

class ManhattanLinearConflict: public Manhattan {
public:
    ManhattanLinearConflict(const Grid* const goal);
    ~ManhattanLinearConflict();
    int calculateAll(const Grid* const state) const;
    int update(const Grid* const state, const pos swapped) const;

private:
    ManhattanLinearConflict();
    int _findConflictsInRow(pos start_a, pos goal_a, const Grid* const state) const;
    int _findConflictsInColumn(pos start_a, pos goal_a, const Grid* const state) const;
};

#endif
