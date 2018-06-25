#include "ManhattanLinearConflict.hpp"

ManhattanLinearConflict::ManhattanLinearConflict() {
}

ManhattanLinearConflict::ManhattanLinearConflict(const Grid* const goal, t_Strategy strategy) :
Manhattan(goal, strategy) {
}

int ManhattanLinearConflict::calculateAll(const Grid* const state) const {
    int manhattanDistances = Manhattan::calculateAll(state);
    int linearConflicts = 0;

    int tile_a, tile_b;
    pos start_a, goal_a;
    pos start_b, goal_b;

    // Check for conflicts in each column
    for (int x = 0; x < state->getSize(); x++) {
        for (int y = 0; y < state->getSize(); y++) {
            start_a = {x,y};
            tile_a = (*state)[start_a];
            goal_a = _goal->searchPos(tile_a);

            // If tile_a has its goal position within the same column,
            // look for conflicts with other tiles down the same column
            if (tile_a != 0 && goal_a.x == x) {
                for (int y_b = y + 1; y_b < state->getSize(); y_b++) {
                    start_b = {x, y_b};
                    tile_b = (*state)[start_b];
                    goal_b = _goal->searchPos(tile_b);
                    if (tile_b != 0 && goal_b.x == x && goal_b.y < goal_a.y)
                        linearConflicts++;
                }
            }
        }
    }

    // Check for conflicts in each row
    for (int y = 0; y < state->getSize(); y++) {
        for (int x = 0; x < state->getSize(); x++) {
            start_a = {x,y};
            tile_a = (*state)[start_a];
            goal_a = _goal->searchPos(tile_a);

            if (tile_a != 0 && goal_a.y == y) {
                for (int x_b = x + 1; x_b < state->getSize(); x_b++){
                    start_b = {x_b, y};
                    tile_b = (*state)[start_b];
                    goal_b = _goal->searchPos(tile_b);
                    if (tile_b != 0 && goal_b.y == y && goal_b.x < goal_a.x)
                        linearConflicts++;
                }
            }
        }
    }
    // std::cout << "Calculated Manhattan + Linearconflicts for the following grid:" << std::endl;
    // std::cout << state->toString() << std::endl;
    // std::cout << "Manhattan distances: " << manhattanDistances << std::endl;
    // std::cout << "Linear conflicts (x2): " << linearConflicts << std::endl;
    return manhattanDistances + 2 * linearConflicts;
}

/*
**  Here, 'swapped' indicates the position of the tile that was just moved.
**  It was previously at the current location of the emtpy square (aka 0).
*/
int ManhattanLinearConflict::update(const Grid* const state, const pos swapped) const {
    int distance = state->get_h_cost();
    int number;
    pos goal_pos;
    pos state_pos;

    number = (*state)[swapped];
    goal_pos = _goal->searchPos(number);

    // Subtract previous manhattan distance of the swapped tile when it was
    // on the empty square.
    state_pos = state->searchPos(0);
    distance -= Manhattan::_manhattan_distance(state_pos, goal_pos);

    // Add manhattan distance of the tile in its new position
    state_pos = swapped;
    distance += Manhattan::_manhattan_distance(state_pos, goal_pos);

    // std::cout << "Number " << number << " was at a manhattan dist of ";
    std::cout << _manhattan_distance(state->searchPos(0), goal_pos);
    // std::cout << " now at " << _manhattan_distance(state_pos, goal_pos) << std::endl;

    // If swap was vertical, update linear conflicts in rows
    if ((state->searchPos(0) - swapped).x == 0) {
        // std::cout << "- subtracting ";
        distance -= _findConflictsInRow(state->searchPos(0), goal_pos, state) * 2;
        // std::cout << "+ adding ";
        distance += _findConflictsInRow(swapped, goal_pos, state) * 2;
    }
    // If swap was horizontal, update linear conflicts in columns
    else if ((state->searchPos(0) - swapped).y == 0) {
        // std::cout << "- subtracting ";
        distance -= _findConflictsInColumn(state->searchPos(0), goal_pos, state) * 2;
        // std::cout << "+ adding ";
        distance += _findConflictsInColumn(swapped, goal_pos, state) * 2;
    }
    else
        throw std::runtime_error("Error in linearConflict update");

    return distance;
}

// Look for linear conflicts between tile_a and all other tiles in its row
int ManhattanLinearConflict::_findConflictsInRow(pos start_a, pos goal_a, const Grid* const state) const {
    int linearConflicts = 0;
    pos start_b, goal_b;
    int tile_b;

    if (start_a.y == goal_a.y) {
        for (int x_b = 0; x_b < state->getSize(); x_b++) {
            start_b = {x_b, start_a.y};
            tile_b = (*state)[start_b];
            goal_b = _goal->searchPos(tile_b);
            if (goal_b.y == goal_a.y)
                if (start_b.x > start_a.x && goal_b.x < goal_a.x){
                    linearConflicts++;
                    // std::cout << "(number " << tile_b << ")";
                }
                if (start_b.x < start_a.x && goal_b.x > goal_a.x){
                    linearConflicts++;
                    // std::cout << "(number " << tile_b << ")";
                }
        }
    }
    // std::cout << linearConflicts << " conflicts in row " << start_a.y << std::endl;
    return linearConflicts;
}

// Look for linear conflicts between tile_a and all other tiles in its column
int ManhattanLinearConflict::_findConflictsInColumn(pos start_a, pos goal_a, const Grid* const state) const {
    int linearConflicts = 0;
    pos start_b, goal_b;
    int tile_b;

    if (start_a.x == goal_a.x) {
        for (int y_b = 0; y_b < state->getSize(); y_b++) {
            start_b = {start_a.x, y_b};
            tile_b = (*state)[start_b];
            goal_b = _goal->searchPos(tile_b);
            if (goal_b.x == goal_a.x)
                if (start_b.y > start_a.y && goal_b.y < goal_a.y)
                    linearConflicts++;
                if (start_b.y < start_a.y && goal_b.y > goal_a.y)
                    linearConflicts++;
        }
    }
    // std::cout << linearConflicts << " conflicts in column " << start_a.x << std::endl;
    return linearConflicts;
}
