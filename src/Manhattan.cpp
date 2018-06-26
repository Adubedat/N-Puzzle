#include "Manhattan.hpp"

Manhattan::Manhattan(): _goal(nullptr) {
}

Manhattan::Manhattan(const Grid* const goal, e_strategy strategy) :
    _goal(goal), _strategy(strategy) {}

int Manhattan::calculateAll(const Grid* const state) const {
    int distance = 0;
    pos state_pos;
    pos goal_pos;
    int number;

    for (int x=0; x < state->getSize(); x++){
        for (int y=0; y < state->getSize(); y++){
            state_pos = {x, y};
            number = (*state)[state_pos];
            if (number > 0){
                goal_pos = _goal->searchPos(number);
                distance += _manhattan_distance(state_pos, goal_pos);
            }
        }
    }
    return (distance);
}

/*
**  Here, 'swapped' indicates the position of the tile that was just moved.
**  It was previously at the current location of the emtpy square (aka 0).
*/
int Manhattan::update(const Grid* const state, const pos swapped) const {
    int distance = state->get_h_cost();
    int number;
    pos goal_pos;
    pos state_pos;

    number = (*state)[swapped];
    goal_pos = _goal->searchPos(number);

    // Subtract previous manhattan distance of the swapped tile when it was
    // on the empty square.
    state_pos = state->searchPos(0);
    distance -= _manhattan_distance(state_pos, goal_pos);

    // Add manhattan distance of the tile in its new position
    state_pos = swapped;
    distance += _manhattan_distance(state_pos, goal_pos);

    return distance;
}

int Manhattan::_manhattan_distance(pos state, pos goal) const {
    int distance = 0;
    distance += ABS(goal.x - state.x);
    distance += ABS(goal.y - state.y);
    return distance;
}

e_strategy  Manhattan::get_strategy() const {
    return this->_strategy;
}
