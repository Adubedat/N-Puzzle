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
    return (0);
}
