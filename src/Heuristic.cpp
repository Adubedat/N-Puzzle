#include "Heuristic.hpp"

int manhattanDistance(Grid* const start, Grid* const goal) {
    int distance = 0;
    int number;
    pos start_pos;
    pos goal_pos;

    for (x=0; x < start->getSize(); x++){
        for (y=0; y < start->getSize(); y++){
            start_pos = {x, y};
            number = (*start)[start_pos];
            if (number > 0){
                goal_pos = goal->_searchPos(number);
                distance += ABS(goal_pos.x - start_pos.x);
                distance += ABS(goal_pos.y - start_pos.y);
            }
        }
    }
    return (distance);
}

int hammingDistance(Grid* const start, Grid* const goal) {
    
}
