#include "Hamming.hpp"

Hamming::Hamming(const Grid* const goal) :
    _goal(goal) {};

int     Hamming::calculateAll(const Grid* const state) {
    int distance = 0;
    pos position;

    for (int x=0; x < _goal->getSize(); x++){
        for (int y=0; y < _goal->getSize(); y++){
            position = {x,y};
            if ((*_goal)[position] != 0 && (*_goal)[position] != (*state)[position])
                distance++;
        }
    }
    return (distance);
}

int     Hamming::update(const Grid* const state, const pos swapped) {
    int distance = state->get_h_cost();
    int number;
    pos old_pos;

    number = (*state)[swapped];
    old_pos = state->searchPos(0);

    // If old_pos was missplaced, remove 1
    if (*_goal)[old_pos] != number)
        distance -= 1;

    // If new_pos is missplaced, add 1
    if (*_goal)[swapped] != number)
        distance += 1;

    return distance;
}
