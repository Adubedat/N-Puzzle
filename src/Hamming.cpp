#include "Hamming.hpp"

Hamming::Hamming(const Grid* const goal, e_strategy strategy) :
    _goal(goal), _strategy(strategy) {};

int     Hamming::calculateAll(const Grid* const state) const {
    int distance = 0;
    pos position;

    for (int x=0; x < static_cast<int>(_goal->getSize()); x++){
        for (int y=0; y < static_cast<int>(_goal->getSize()); y++){
            position = {x,y};
            if ((*_goal)[position] != 0 && (*_goal)[position] != (*state)[position])
                distance++;
        }
    }
    return (distance);
}

int     Hamming::update(const Grid* const state, const pos swapped) const {
    int distance = state->get_h_cost();
    int number;
    pos old_pos;

    number = (*state)[swapped];
    old_pos = state->searchPos(0);

    // If old_pos was missplaced, remove 1
    if ((*_goal)[old_pos] != number)
        distance -= 1;

    // If new_pos is missplaced, add 1
    if ((*_goal)[swapped] != number)
        distance += 1;

    return distance;
}
e_strategy  Hamming::get_strategy() const {
    return this->_strategy;
}
