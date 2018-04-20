#include "Heuristic.hpp"

int manhattanDistance(Grid* const start, Grid* const goal) {
    int distance = 0;
    int number;
    pos start_pos;
    pos goal_pos;

    for (int x=0; x < start->getSize(); x++){
        for (int y=0; y < start->getSize(); y++){
            start_pos = {x, y};
            number = (*start)[start_pos];
            if (number > 0){
                goal_pos = goal->searchPos(number);
                distance += ABS(goal_pos.x - start_pos.x);
                distance += ABS(goal_pos.y - start_pos.y);
            }
        }
    }
    return (distance);
}

int hammingDistance(Grid* const start, Grid* const goal) {
    int distance = 0;
    pos position;

    for (int x=0; x < goal->getSize(); x++){
        for (int y=0; y < goal->getSize(); y++){
            position = {x,y};
            if ((*goal)[position] != 0 && (*goal)[position] != (*start)[position])
                distance++;
        }
    }
    return (distance);
}
